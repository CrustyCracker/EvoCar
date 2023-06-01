#include <iostream>
#include <numeric>
#include <random>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "implot.h"

#include "../config/Config.h"
#include "Car.h"
#include "Shape.h"
#include "Render.h"
#include "EvolutionaryAlgorithm.h"

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

    ImGui::CreateContext();
    ImPlot::CreateContext();

    // Initialize ImGui-SFML
    ImGui::SFML::Init(w);

    // Change imgui.ini location
    ImGui::GetIO().IniFilename = "build/imgui.ini";

    // Containers to hold objects we create
    std::vector<Box> boxes;
    std::vector<Car> cars;

    // Add a wall (uses "ground" object, for now)
    Box wall = createGround(world, 50, 350, 100, 700, sf::Color(50, 50, 50));
    boxes.push_back(wall);

    // Generate ground
    Box ground = createGround(world, 350, 50, 500, 100, sf::Color(50, 50, 50));
    boxes.push_back(ground);

    auto vertices_gen = createVertices(
        {2.54951f, 2.12132f, 2.12132f, 2.54951f, 2.54951f, 2.12132f, 2.12132f, 2.54951f},
        {33.7f, 90.0f, 33.7f, 22.6f, 33.7f, 90.0f, 33.7f, 22.6f});

    std::random_device rd;                            // obtain a random number from hardware
    std::mt19937 gen(rd());                           // seed the generator
    std::uniform_int_distribution<> distr(150, 350);  // define the range

    sf::Color bodyColor = sf::Color(50, 200, 50);
    sf::Color wheelColor = sf::Color(225, 50, 50);

    EvolutionaryAlgorithm ea(10, Config::SAVE_TO_FILE);

    for (int i = 0; i < ea.getPopulationSize(); ++i) {
        Car car = Car(world, distr(gen), 300, vertices_gen, 100.0f, 25.0f, bodyColor, wheelColor);
        cars.push_back(car);
    }

    // Make cars pass through eachother
    // by setting collision filtering
    b2Filter filter;
    filter.categoryBits = 2;
    filter.maskBits = 1;
    for (Car car : cars) {
        car.setCollisionFilter(filter);
    }

    bool paused = false;
    bool pause_check = true;

    std::vector<float> v_axis(Config::VELOCITY_ARRAY_SIZE);
    std::vector<float> v_values(Config::VELOCITY_ARRAY_SIZE);

    std::iota(std::begin(v_axis), std::end(v_axis), 1);

    sf::Clock deltaClock;
    /** PROGRAM LOOP **/
    while (w.isOpen()) {
        // Update the world, standard arguments
        if (!paused) {
            world->Step(1 / 60.f, 6, 3);
        }
        // Render everything
        render(w, boxes, cars);

        ImGui::SFML::Update(w, deltaClock.restart());

        ImGui::SetNextWindowSize(ImVec2(420, 130), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::Begin("Car Demo");
        ImGui::Text("Left/Right arrow keys to rotate the wheels.");
        ImGui::Text("Hold C to attach the camera to the car.");
        ImGui::Text("\n");

        ImGui::BeginChild("Car Settings");

        ImGui::SliderFloat("Wheel 1 Radius [px]", &cars[0].getFrontWheel()->radius, 0.0f, 100.0f);
        cars[0].getFrontWheel()->body->GetFixtureList()->GetShape()->m_radius =
            cars[0].getFrontWheel()->radius / Config::PPM;

        ImGui::SliderFloat("Wheel 2 Radius [px]", &cars[0].getBackWheel()->radius, 0.0f, 100.0f);
        cars[0].getBackWheel()->body->GetFixtureList()->GetShape()->m_radius =
            cars[0].getBackWheel()->radius / Config::PPM;
        ImGui::EndChild();

        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(440, 10), ImGuiCond_FirstUseEver);
        ImGui::Begin("Car's Position");
        ImGui::Text("Car's position: (%.1f, %.1f)",
                    cars[0].getBody()->body->GetPosition().x * Config::PPM,
                    cars[0].getBody()->body->GetPosition().y * Config::PPM);
        ImGui::Text("Car's angle: %.1f", cars[0].getBody()->body->GetAngle() * 180 / b2_pi);
        ImGui::End();

        Box lastGround = boxes.back();
        ImGui::SetNextWindowPos(ImVec2(440, 80), ImGuiCond_FirstUseEver);
        ImGui::Begin("Last Ground's Right Edge's Position");
        ImGui::Text("Last ground's right edge's position: %.1f",
                    lastGround.body->GetPosition().x * Config::PPM + lastGround.width / 2);
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(230, 340), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(10, 144), ImGuiCond_FirstUseEver);
        ImGui::Begin("Car's Velocity");
        ImPlot::SetNextAxesToFit();
        if (ImPlot::BeginPlot("Velocity")) {
            if (!paused) {
                v_axis.push_back(v_axis.back() + 1);
                v_values.push_back(cars[0].getVelocity());
            }
            std::vector<float> v_axis_crop =
                std::vector<float>(v_axis.end() - Config::VELOCITY_ARRAY_SIZE, v_axis.end());
            std::vector<float> v_values_crop =
                std::vector<float>(v_values.end() - Config::VELOCITY_ARRAY_SIZE, v_values.end());
            ImPlot::PlotLine("V", &(v_axis_crop[0]), &(v_values_crop[0]),
                             Config::VELOCITY_ARRAY_SIZE);
            ImPlot::EndPlot();
        }
        ImGui::End();

        const float generateDistance = 200;
        // if car is far enough to the right, generate a new ground
        if (lastGround.body->GetPosition().x * Config::PPM + lastGround.width / 2 <
            cars[0].getBody()->body->GetPosition().x * Config::PPM + generateDistance) {
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
                sf::View(sf::Vector2f(cars[0].getBody()->body->GetPosition().x * Config::PPM,
                                      Config::WINDOW_HEIGHT -
                                          (cars[0].getBody()->body->GetPosition().y * Config::PPM)),
                         sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
            cameraView.setRotation((-1) * cars[0].getBody()->body->GetAngle() * 180 / b2_pi);
            w.setView(cameraView);
        } else {
            // Reset camera
            sf::View cameraView =
                sf::View(sf::Vector2f(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2),
                         sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
            w.setView(cameraView);
        }

        if (!paused) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                // Rotate the circles left
                cars[0].getFrontWheel()->body->ApplyTorque(1000, false);
                cars[0].getBackWheel()->body->ApplyTorque(1000, false);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                // Rotate the circles right
                cars[0].getFrontWheel()->body->ApplyTorque(-1000, false);
                cars[0].getBackWheel()->body->ApplyTorque(-1000, false);
            }
        }

        // simplified air drag
        //
        // F = V^2 * k
        // k ≈ 1/2 * ρ * A * C_d ≈ 3.4
        // ρ = 1.293 kg/m^3
        // A = ? (let's assume 5 m^2)
        // C_d = ? (let's assume 1.05)
        //
        // F = 3.4 * V^2

        cars[0].getBody()->body->ApplyForceToCenter(
            b2Vec2(-1.84 * cars[0].getBody()->body->GetLinearVelocity().x *
                       abs(cars[0].getBody()->body->GetLinearVelocity().x),
                   -1.84 * cars[0].getBody()->body->GetLinearVelocity().y *
                       abs(cars[0].getBody()->body->GetLinearVelocity().y)),
            true);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            // Close the window
            w.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            // Pause the simulation
            if (pause_check) {
                paused = !paused;
                pause_check = false;
            }
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
            // Allow user to toggle pause again
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Space) {
                    pause_check = true;
                }
            }
        }
    }

    ImGui::SFML::Shutdown();

    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    return 0;
}
