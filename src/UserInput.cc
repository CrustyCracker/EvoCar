#include "UserInput.h"

/*
Author:         Jakub Marcowski
Description:    File containing user input functions.
*/

void handleUserInput(sf::RenderWindow &w, bool &paused, bool &pause_check, bool &next_gen) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
            // Generate the next generation
            if (nxt_g_check) {
                next_gen = true;
                nxt_g_check = false;
            }
        }
    }
}

void handleEvents(sf::RenderWindow &w, bool &pause_check, bool &nxt_g_check, bool &focus) {
    // Process events
    sf::Event event;
    while (w.pollEvent(event)) {
        if (event.type == sf::Event::GainedFocus) {
            focus = true;
        }
        if (event.type == sf::Event::LostFocus) {
            focus = false;
        }
        if (focus) {
            ImGui::SFML::ProcessEvent(event);
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                w.close();
                ImGui::SFML::Shutdown();
            }
            if (event.type == sf::Event::KeyReleased) {
                // Allow user to toggle pause again
                if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Space) {
                    pause_check = true;
                }
                // Allow user to generate the next generation again
                if (event.key.code == sf::Keyboard::N) {
                    nxt_g_check = true;
                }
            }
        }
    }
}
