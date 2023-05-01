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
Author:
Description:
*/

b2World world(b2Vec2(0, Config::GRAVITIATIONAL_ACCELERATION));

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

    // Container to hold all the boxes we create
    std::vector<Box*> boxes;

    // Container to hold all the polygons we create
    std::vector<Polygon*> polygons;

    // Container to hold all the circles we create
    std::vector<Circle*> circles;

    // Generate ground
    Box ground = createGround(&world, 350, 50, 500, 100, sf::Color(50, 50, 50));
    boxes.push_back(&ground);

    // Add a wall (uses "ground" object, for now)
    Box wall = createGround(&world, 50, 350, 100, 700, sf::Color(50, 50, 50));
    boxes.push_back(&wall);

    float carColor[3] = {(float)200 / 255, (float)50 / 255, (float)50 / 255};
    CarAlt car = CarAlt(&world, 350, 300, carColor);

    // VVV see https://stackoverflow.com/a/46330927/14664861 VVV

    // auto carBody = car.getBody();
    // auto carFrontWheel = car.getFrontWheel();
    // auto carBackWheel = car.getBackWheel();

    polygons.push_back(car.getBody());
    circles.push_back(car.getFrontWheel());
    circles.push_back(car.getBackWheel());

    sf::Clock deltaClock;
    /** GAME LOOP **/
    while (w.isOpen()) {
        // Update the world, standard arguments
        world.Step(1 / 60.f, 6, 3);
        // Render everything
        render(w, boxes, polygons, circles);

        ImGui::SFML::Update(w, deltaClock.restart());

        ImGui::SetNextWindowSize(ImVec2(420, 160), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::Begin("Car Demo");
        ImGui::Text("Left/Right arrow keys to rotate the wheels.");
        ImGui::Text("Hold C to attach the camera to the car.");
        ImGui::Text("");

        ImGui::BeginChild("Car Settings");
        ImGui::ColorEdit3("\"Body\" Color", carColor);
        car.getBody()->color =
            sf::Color((int)(carColor[0] * 255), (int)(carColor[1] * 255), (int)(carColor[2] * 255));

        ImGui::SliderFloat("Wheel 1 Radius [px]", &car.getFrontWheel()->radius, 0.0f, 100.0f);
        car.getFrontWheel()->body->GetFixtureList()->GetShape()->m_radius =
            car.getFrontWheel()->radius / Config::PPM;

        ImGui::SliderFloat("Wheel 2 Radius [px]", &car.getBackWheel()->radius, 0.0f, 100.0f);
        car.getBackWheel()->body->GetFixtureList()->GetShape()->m_radius =
            car.getBackWheel()->radius / Config::PPM;
        ImGui::EndChild();

        ImGui::End();

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
