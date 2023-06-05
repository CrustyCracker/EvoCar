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
    if(sf:Keyboard::isKeyPressed(sf::Keyboard::N)){
        next_gen = true;
    }

    
}

void handleEvents(sf::RenderWindow &w, bool &pause_check) {
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
