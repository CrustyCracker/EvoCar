#include <iostream>

#include "../config/config.h"
#include "SFML/Graphics.hpp"
#include "box.h"
#include "box2d/box2d.h"
#include "car.h"
#include "circle.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "polygon.h"
#include "render.h"

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
    std::vector<Box> boxes;

    // Container to hold all the polygons we create
    std::vector<Polygon> polygons;

    // Container to hold all the circles we create
    std::vector<Circle> circles;

    // Generate ground
    boxes.push_back(createGround(&world, 350, 50, 500, 100, sf::Color(50, 50, 50)));

    // Add a wall (uses "ground" object, for now)
    boxes.push_back(createGround(&world, 50, 350, 100, 700, sf::Color(50, 50, 50)));

    float carColor[3] = {(float)200 / 255, (float)50 / 255, (float)50 / 255};
    Polygon polygon = createCar(&world, &polygons, &circles, carColor);

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
        polygons[0].color =
            sf::Color((int)(carColor[0] * 255), (int)(carColor[1] * 255), (int)(carColor[2] * 255));

        ImGui::SliderFloat("Wheel 1 Radius [px]", &circles[0].radius, 0.0f, 100.0f);
        circles[0].body->GetFixtureList()->GetShape()->m_radius = circles[0].radius / Config::PPM;

        ImGui::SliderFloat("Wheel 2 Radius [px]", &circles[1].radius, 0.0f, 100.0f);
        circles[1].body->GetFixtureList()->GetShape()->m_radius = circles[1].radius / Config::PPM;
        ImGui::EndChild();

        ImGui::End();

        ImGui::SFML::Render(w);

        w.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            // Attach camera to the polygon
            sf::View cameraView = sf::View(
                sf::Vector2f(polygon.body->GetPosition().x * Config::PPM,
                             Config::WINDOW_HEIGHT - (polygon.body->GetPosition().y * Config::PPM)),
                sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
            cameraView.setRotation((-1) * polygon.body->GetAngle() * 180 / b2_pi);
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
            for (const auto &circle : circles) {
                circle.body->ApplyTorque(1000, false);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            // Rotate the circles right
            for (const auto &circle : circles) {
                circle.body->ApplyTorque(-1000, false);
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
        }
    }
    ImGui::SFML::Shutdown();
    return 0;
}
