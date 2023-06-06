/**
 * @brief Header for a file containing user input functions.
 *
 * @file UserInput.h
 * @authors Jakub Marcowski
 * @date 2023-06-06
 */

#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

/**
 * @brief Function for handling user inputs.
 *
 * @param w SFML's RenderWindow.
 * @param paused Whether the simulation is paused (bool).
 * @param pause_check Whether the `paused` was turned on (bool).
 * @param next_gen Whether the program should generate the next generation (bool).
 * @param nxt_g_check Whether the `next_gen` was turned on (bool).
 * @param focus Whether the window is in focus (bool).
 */
void handleUserInput(sf::RenderWindow &w, bool &paused, bool &pause_check, bool &next_gen,
                     bool &nxt_g_check, bool &focus);

/**
 * @brief Function for handling SFML events.
 *
 * @param w SFML's RenderWindow.
 * @param pause_check Whether the `paused` was turned on (bool).
 * @param nxt_g_check Whether the `next_gen` was turned on (bool).
 * @param focus Whether the window is in focus (bool).
 */
void handleEvents(sf::RenderWindow &w, bool &pause_check, bool &nxt_g_check, bool &focus);

#endif
