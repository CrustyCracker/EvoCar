#include <iostream>
#include <filesystem>

#include "box2d/box2d.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "implot.h"
#include "SFML/Graphics.hpp"

#include "../config/Config.h"
#include "../config/MapGenConfig.h"
#include "Car.h"
#include "EvolutionaryAlgorithm.h"
#include "Render.h"
#include "Shape.h"
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
    std::vector<Polygon> groundVector;
    std::vector<Car> cars;

    // Generate ground
    std::vector<b2Vec2> groundVertecies = {b2Vec2(0, 0),
                                           b2Vec2(MapGenConfig::GROUND_PART_LENGTH, 0),
                                           b2Vec2(0, -MapGenConfig::GROUND_LEG_LENGTH)};
    Polygon ground =
        createGround(world, MapGenConfig::GROUND_STARTING_X, MapGenConfig::GROUND_STARTING_Y,
                     groundVertecies, sf::Color(18, 36, 35));
    groundVector.push_back(ground);

    EvolutionaryAlgorithm ea(EvolutionaryAlgorithmConfig::POPULATION_SIZE, Config::SAVE_TO_FILE);

    for (Chromosome chromosome : ea.getPopulation()) {
        cars.push_back(generateCar(world, chromosome));
    }

    bool paused = false;     // Should we pause the simulation?
    bool pauseCheck = true;  // Should we check if the user wants to flip `paused`?
    bool nextGen = false;    // Should we generate the next generation?
    bool nextGCheck = true;  // Should we check if the user wants to flip `nextGen`?
    bool focus = true;       // Is the window in focus? (used to prevent input when not in focus)
    int timer = 0;

    std::filesystem::path filePath = std::filesystem::path(__FILE__);
    std::filesystem::path dirPath = filePath.parent_path();

    std::cout << "Directory Path: " << dirPath << std::endl;

    // Append the relative paths
    std::string iconPath = (dirPath / "../resources/placeholder_icon.png").string();
    std::string backgroundPath = (dirPath / "../resources/background_img.jpg").string();

    // Set window icon
    auto icon = sf::Image{};
    if (icon.loadFromFile(iconPath)) {
        w.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    // Load background image
    sf::Texture background;
    background.loadFromFile(backgroundPath);
    sf::Sprite bg(background);
    bg.setScale(sf::Vector2f(Config::WINDOW_WIDTH / bg.getLocalBounds().width,
                             Config::WINDOW_HEIGHT / bg.getLocalBounds().height));

    sf::Clock deltaClock;
    /** PROGRAM LOOP **/
    while (w.isOpen()) {
        // Update the world, standard arguments
        if (!paused) {
            world->Step(1 / 60.0f, 6, 3);
            ++timer;
            if (timer >= Config::GENERATION_TIME) {
                nextGen = true;
                timer = 0;
            }
        }

        if (nextGen) {
            nextGen = false;
            for (int i = 0; i < cars.size(); ++i) {
                ea.setFitness(i, cars[i].getPosX());
            }
            ea.nextGeneration();
            removeCars(world, &cars);
            for (Chromosome chromosome : ea.getPopulation()) {
                cars.push_back(generateCar(world, chromosome));
            }
            timer = 0;
        }

        // Render everything
        render(w, bg, groundVector, cars);

        ImGui::SFML::Update(w, deltaClock.restart());

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.071f, 0.141f, 0.137f, 0.5f));

        ImGui::SetNextWindowSize(ImVec2(340, 340), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::Begin("Cars' Velocity");
        ImPlot::SetNextAxesToFit();
        if (ImPlot::BeginPlot("Velocity")) {
            ImPlot::SetupLegend(ImPlotLocation_West, ImPlotLegendFlags_Outside);
            for (int i = 0; i < cars.size(); ++i) {
                char i_str[11];  // 10 digits + null
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

        generateGround(world, &groundVector, cars);

        ImGui::SFML::Render(w);

        w.display();

        // Attach camera to the car's body
        sf::View cameraView =
            sf::View(sf::Vector2f(getFurthestCarX(cars) * Config::PPM, 0.5 * Config::WINDOW_HEIGHT),
                     sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
        w.setView(cameraView);

        // Move background sprite with camera
        bg.setPosition(cameraView.getCenter() -
                       sf::Vector2f(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2));

        if (!paused) {
            for (int i = 0; i < cars.size(); ++i) {
                cars[i].getFrontWheel()->body->ApplyTorque(-CarConfig::CAR_TORQUE, false);
                cars[i].getBackWheel()->body->ApplyTorque(-CarConfig::CAR_TORQUE, false);
                applyAirResistance(cars[i]);
            }
        }

        // Display FPS in window title
        w.setTitle("EvoRacer, FPS: " + std::to_string((int)ImGui::GetIO().Framerate));

        handleEvents(w, pauseCheck, nextGCheck, focus);
        handleUserInput(w, paused, pauseCheck, nextGen, nextGCheck, focus);
    }

    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    return 0;
}
