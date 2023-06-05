/*
Author:         Jakub Marcowski
Description:    Header for a file containing user input functions.
*/

#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

void handleUserInput(sf::RenderWindow &w, bool &paused, bool &pause_check, bool &next_gen,
                     bool &nxt_g_check, bool &focus);

void handleEvents(sf::RenderWindow &w, bool &pause_check, bool &nxt_g_check, bool &focus);

#endif
