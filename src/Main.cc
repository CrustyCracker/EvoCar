#include <iostream>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "imgui-SFML.h"
#include "imgui.h"

#include "../config/Config.h"
#include "Car.h"
#include "Shape.h"
#include "Render.h"

/*
Author:        Jakub Marcowski, Mateusz Krakowski
Description:   Main file for the project, contains the main loop.
*/
typedef std::shared_ptr<b2World> b2WorldPtr;

// initialize the world as a shared pointer
b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITIATIONAL_ACCELERATION));

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Setup SFML window
    sf::RenderWindow w(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "SFML + Box2D",
                       sf::Style::Default, settings);
    w.setFramerateLimit(60);

    // Initialize ImGui-SFML
    ImGui::SFML::Init(w);

    // Change imgui.ini location
    ImGui::GetIO().IniFilename = "build/imgui.ini";

    // Containers to hold objects we create
    std::vector<Box> boxes;
    std::vector<Car *> cars;

    // Add a wall (uses "ground" object, for now)
    Box wall = createGround(world, 50, 350, 100, 700, sf::Color(50, 50, 50));
    boxes.push_back(wall);

    // Generate ground
    Box ground = createGround(world, 350, 50, 500, 100, sf::Color(50, 50, 50));
    boxes.push_back(ground);

    std::vector<b2Vec2> vertices;
    vertices.push_back(b2Vec2(-2.5f, -0.5f));
    vertices.push_back(b2Vec2(-1.5f, -1.5f));
    vertices.push_back(b2Vec2(1.5f, -1.5f));
    vertices.push_back(b2Vec2(2.5f, -0.5f));
    vertices.push_back(b2Vec2(2.5f, 0.5f));
    vertices.push_back(b2Vec2(1.5f, 1.5f));
    vertices.push_back(b2Vec2(-1.5f, 1.5f));
    vertices.push_back(b2Vec2(-2.5f, 0.5f));

    auto vertices2 = createVertices({2, 3, 3, 2, 2, 1, 1, 2});

    sf::Color bodyColor = sf::Color(50, 200, 50);
    sf::Color wheelColor = sf::Color(225, 50, 50);
    Car car = Car(world, 255, 400, vertices, 100.0f, 0.3f, 25.0f, bodyColor, wheelColor);

    sf::Color bodyColor2 = sf::Color(25, 100, 25);
    sf::Color wheelColor2 = sf::Color(113, 25, 25);
    Car car2 = Car(world, 225, 300, vertices2, 100.0f, 0.3f, 25.0f, bodyColor2, wheelColor2);

    sf::Color bodyColor3 = sf::Color(13, 50, 13);
    sf::Color wheelColor3 = sf::Color(57, 13, 13);
    Car car3 = Car(world, 195, 200, vertices, 100.0f, 0.3f, 25.0f, bodyColor3, wheelColor3);

    cars.push_back(&car3);
    cars.push_back(&car2);
    cars.push_back(&car);

    // Make cars pass through eachother
    // by setting collision filtering
    b2Filter filter;
    filter.categoryBits = 2;
    filter.maskBits = 1;
    for (Car *car : cars) {
        car->setCollisionFilter(filter);
    }

    sf::Clock deltaClock;
    /** PROGRAM LOOP **/
    while (w.isOpen()) {
        // Update the world, standard arguments
        world->Step(1 / 60.f, 6, 3);
        // Render everything
        render(w, boxes, cars);

        ImGui::SFML::Update(w, deltaClock.restart());

        ImGui::SetNextWindowSize(ImVec2(420, 130), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::Begin("Car Demo");
        ImGui::Text("Left/Right arrow keys to rotate the wheels.");
        ImGui::Text("Hold C to attach the camera to the car.");
        ImGui::Text("");

        ImGui::BeginChild("Car Settings");

        ImGui::SliderFloat("Wheel 1 Radius [px]", &car.getFrontWheel()->radius, 0.0f, 100.0f);
        car.getFrontWheel()->body->GetFixtureList()->GetShape()->m_radius =
            car.getFrontWheel()->radius / Config::PPM;

        ImGui::SliderFloat("Wheel 2 Radius [px]", &car.getBackWheel()->radius, 0.0f, 100.0f);
        car.getBackWheel()->body->GetFixtureList()->GetShape()->m_radius =
            car.getBackWheel()->radius / Config::PPM;
        ImGui::EndChild();

        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(440, 10), ImGuiCond_FirstUseEver);
        ImGui::Begin("Car's Position");
        ImGui::Text("Car's position: (%.1f, %.1f)",
                    car.getBody()->body->GetPosition().x * Config::PPM,
                    car.getBody()->body->GetPosition().y * Config::PPM);
        ImGui::Text("Car's angle: %.1f", car.getBody()->body->GetAngle() * 180 / b2_pi);
        ImGui::End();

        Box lastGround = boxes.back();
        ImGui::SetNextWindowPos(ImVec2(440, 80), ImGuiCond_FirstUseEver);
        ImGui::Begin("Last Ground's Right Edge's Position");
        ImGui::Text("Last ground's right edge's position: %.1f",
                    lastGround.body->GetPosition().x * Config::PPM + lastGround.width / 2);
        ImGui::End();

        const float generateDistance = 200;
        // if car is far enough to the right, generate a new ground
        if (lastGround.body->GetPosition().x * Config::PPM + lastGround.width / 2 <
            car.getBody()->body->GetPosition().x * Config::PPM + generateDistance) {
            Box ground = createGround(
                world, lastGround.body->GetPosition().x * Config::PPM + lastGround.width, 50, 500,
                100, sf::Color(50, 50, 50));
            boxes.push_back(ground);
        }

        ImGui::SFML::Render(w);

        w.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            // Attach camera to the car's body
            sf::View cameraView =
                sf::View(sf::Vector2f(car.getBody()->body->GetPosition().x * Config::PPM,
                                      Config::WINDOW_HEIGHT -
                                          (car.getBody()->body->GetPosition().y * Config::PPM)),
                         sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
            cameraView.setRotation((-1) * car.getBody()->body->GetAngle() * 180 / b2_pi);
            w.setView(cameraView);
        } else {
            // Reset camera
            sf::View cameraView =
                sf::View(sf::Vector2f(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2),
                         sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
            w.setView(cameraView);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // Rotate the circles left
            car.getFrontWheel()->body->ApplyTorque(1000, false);
            car.getBackWheel()->body->ApplyTorque(1000, false);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            // Rotate the circles right
            car.getFrontWheel()->body->ApplyTorque(-1000, false);
            car.getBackWheel()->body->ApplyTorque(-1000, false);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            // Close the window
            w.close();
        }

        // Display FPS in window title
        w.setTitle("SFML + Box2D, FPS: " + std::to_string((int)ImGui::GetIO().Framerate));

        // Process events
        sf::Event event;
        while (w.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                w.close();
            }
        }
    }
    ImGui::SFML::Shutdown();
    return 0;
}
