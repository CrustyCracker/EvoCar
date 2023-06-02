#include <iostream>

#include "box2d/box2d.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "implot.h"
#include "SFML/Graphics.hpp"

#include "../config/Config.h"
#include "Car.h"
#include "EvolutionaryAlgorithm.h"
#include "Shape.h"
#include "Render.h"
#include "UserInput.h"
#include "Utility.h"

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
    ImGui::GetIO().IniFilename = "./imgui.ini";

    // Containers to hold objects we create
    std::vector<Box> boxes;
    std::vector<Car> cars;

    // Generate ground
    Box ground = createGround(world, -150, 50, 500, 100, sf::Color(18, 36, 35));
    boxes.push_back(ground);

    EvolutionaryAlgorithm ea(EvolutionaryAlgorithmConfig::POPULATION_SIZE, Config::SAVE_TO_FILE);

    for (int i = 0; i < ea.getPopulationSize(); ++i) {
        cars.push_back(generateRandomCar(world));
    }

    bool paused = false;
    bool pause_check = true;

    // Set window icon
    auto icon = sf::Image{};
    if (icon.loadFromFile("../resources/placeholder_icon.png")) {
        w.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    // Load background image
    sf::Texture background;
    background.loadFromFile("../resources/background_img.jpg");
    sf::Sprite bg(background);
    bg.setScale(sf::Vector2f(Config::WINDOW_WIDTH / bg.getLocalBounds().width,
                             Config::WINDOW_HEIGHT / bg.getLocalBounds().height));

    sf::Clock deltaClock;
    /** PROGRAM LOOP **/
    while (w.isOpen()) {
        // Update the world, standard arguments
        if (!paused) {
            world->Step(1 / 60.f, 6, 3);
        }
        // Render everything
        render(w, bg, boxes, cars);

        ImGui::SFML::Update(w, deltaClock.restart());

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.071f, 0.141f, 0.137f, 0.5f));

        ImGui::SetNextWindowSize(ImVec2(340, 340), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::Begin("Cars' Velocity");
        ImPlot::SetNextAxesToFit();
        if (ImPlot::BeginPlot("Velocity")) {
            for (int i = 0; i < cars.size(); ++i) {
                char i_str[10];
                sprintf(i_str, "%d", i);

                if (!paused) {
                    cars[i].getVelX()->push_back(cars[i].getVelX()->back() + 1);
                    cars[i].getVelY()->push_back(cars[i].getVelocity());
                }
                std::vector<float> v_axis_crop =
                    std::vector<float>(cars[i].getVelX()->end() - Config::VELOCITY_ARRAY_SIZE,
                                       cars[i].getVelX()->end());
                std::vector<float> v_values_crop =
                    std::vector<float>(cars[i].getVelY()->end() - Config::VELOCITY_ARRAY_SIZE,
                                       cars[i].getVelY()->end());
                ImPlot::PushStyleColor(ImPlotCol_Line, SFMLColorToImVec4(cars[i].getBodyColor()));
                ImPlot::PlotLine(i_str, &(v_axis_crop[0]), &(v_values_crop[0]),
                                 Config::VELOCITY_ARRAY_SIZE);
                ImPlot::PopStyleColor();
            }
            ImPlot::EndPlot();
        }
        ImGui::End();

        ImGui::PopStyleColor();

        generateGround(world, &boxes, cars);

        ImGui::SFML::Render(w);

        w.display();

        // Attach camera to the car's body
        sf::View cameraView =
            sf::View(sf::Vector2f(cars[0].getBody()->body->GetPosition().x * Config::PPM,
                                  0.5 * Config::WINDOW_HEIGHT),
                     sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
        w.setView(cameraView);

        // Move background sprite with camera
        bg.setPosition(cameraView.getCenter() -
                       sf::Vector2f(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2));

        if (!paused) {
            for (int i = 0; i < cars.size(); ++i) {
                cars[i].getFrontWheel()->body->ApplyTorque(-1000 + (i * 10), false);
                cars[i].getBackWheel()->body->ApplyTorque(-1000 + (i * 10), false);
            }
        }

        for (Car car : cars) {
            applyAirResistance(car);
        }

        handleUserInput(w, paused, pause_check);

        // Display FPS in window title
        w.setTitle("SFML + Box2D, FPS: " + std::to_string((int)ImGui::GetIO().Framerate));

        handleEvents(w, pause_check);
    }

    ImGui::SFML::Shutdown();

    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    return 0;
}
