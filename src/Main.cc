/**
 * @brief Main file for the project, contains the main loop.
 *
 * @file Main.cc
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-07
 */

#include "box2d/box2d.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "implot.h"
#include "SFML/Graphics.hpp"

#include "../config/Config.h"
#include "../config/MapGenConfig.h"
#include "Car.h"
#include "EvolutionaryAlgorithm.h"
#include "GUI.h"
#include "Render.h"
#include "Shape.h"
#include "UserInput.h"
#include "Utility.h"

typedef std::shared_ptr<b2World> b2WorldPtr;

// initialize the world as a shared pointer
b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Setup SFML window
    sf::RenderWindow w(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "EvoRacer",
                       sf::Style::Default, settings);
    w.setFramerateLimit(Config::MAX_FPS);

    // Initialize ImGui and all its friends
    ImGui::SFML::Init(w);
    ImPlot::CreateContext();

    // Change imgui.ini location
    ImGui::GetIO().IniFilename = "./imgui.ini";

    // Containers to hold objects we create
    std::vector<Polygon> groundVector;
    std::vector<Car> cars;

    // Generate ground
    std::vector<b2Vec2> groundVertices = {b2Vec2(0, 0), b2Vec2(MapGenConfig::GROUND_PART_LENGTH, 0),
                                          b2Vec2(0, -MapGenConfig::GROUND_LEG_LENGTH)};
    Polygon ground =
        createGround(world, MapGenConfig::GROUND_STARTING_X, MapGenConfig::GROUND_STARTING_Y,
                     groundVertices, sf::Color(18, 36, 35));
    groundVector.push_back(ground);

    EvolutionaryAlgorithm ea(EvolutionaryAlgorithmConfig::POPULATION_SIZE, Config::SAVE_TO_FILE);

    for (const Chromosome& chromosome : ea.getPopulation()) {
        cars.push_back(generateCar(world, chromosome));
    }

    bool paused = false;     // Should we pause the simulation?
    bool pauseCheck = true;  // Should we check if the user wants to flip `paused`?
    bool nextGen = false;    // Should we generate the next generation?
    bool nextGCheck = true;  // Should we check if the user wants to flip `nextGen`?
    bool focus = true;       // Is the window in focus? (used to prevent input when not in focus)
    int timer = 0;

    // Set window icon
    setIcon(w);

    auto textures = loadBGTextures();
    auto sprites = loadBGSprites(textures, cars);

    sf::Clock deltaClock;
    /** PROGRAM LOOP **/
    while (w.isOpen()) {
        // Update the world, standard arguments
        if (!paused) {
            world->Step(1 / 60.0f, 6, 3);
            ++timer;
            if (timer >= Config::GENERATION_TIME) {
                nextGen = true;
            }
        }

        if (nextGen) {
            nextGen = false;
            for (int i = 0; i < cars.size(); ++i) {
                ea.setFitness(i, cars[i].getPosX());
            }
            ea.nextGeneration();
            removeCars(world, &cars);
            for (const Chromosome& chromosome : ea.getPopulation()) {
                cars.push_back(generateCar(world, chromosome));
            }
            timer = 0;
        }

        // Render everything
        render(w, sprites, groundVector, cars);

        ImGui::SFML::Update(w, deltaClock.restart());

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.071f, 0.141f, 0.137f, 0.5f));

        ImGui::SetNextWindowSize(ImVec2(340, 340), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        renderVelocityPlot(cars, paused);

        ImGui::SetNextWindowSize(ImVec2(340, 340), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(930, 10), ImGuiCond_FirstUseEver);
        renderPositionPlot(cars, paused);

        ImGui::SetNextWindowSize(ImVec2(175, 75), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(543, 10), ImGuiCond_FirstUseEver);
        printEAInfo(ea);

        ImGui::PopStyleColor();

        generateGround(world, &groundVector, cars);

        ImGui::SFML::Render(w);

        w.display();

        // Attach camera to the car's body
        sf::View cameraView =
            sf::View(sf::Vector2f(getFurthestCarPos(cars).x * Config::PPM,
                                  Config::WINDOW_HEIGHT - getFurthestCarPos(cars).y * Config::PPM),
                     sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
        w.setView(cameraView);

        // If the camera moves, shift backgrounds accordingly to create a parallax effect
        for (int i = 0; i < 5; ++i) {
            sprites[i].setPosition(
                cameraView.getCenter().x * (1.0 - 0.2 * i) - Config::WINDOW_WIDTH * (1.4 - 0.1 * i),
                cameraView.getCenter().y - Config::WINDOW_HEIGHT / 2.0);
        }

        if (!paused) {
            for (auto& car : cars) {
                car.getFrontWheel()->body->ApplyTorque(-CarConfig::CAR_TORQUE, false);
                car.getBackWheel()->body->ApplyTorque(-CarConfig::CAR_TORQUE, false);
                applyAirResistance(car);
            }
        }

        // Display FPS in window title
        w.setTitle("EvoRacer, FPS: " + std::to_string((int)ImGui::GetIO().Framerate));

        handleEvents(w, pauseCheck, nextGCheck, focus);
        handleUserInput(w, paused, pauseCheck, nextGen, nextGCheck, focus);
    }

    freeBGTextures(textures);

    ImPlot::DestroyContext();
    ImGui::SFML::Shutdown();

    return 0;
}
