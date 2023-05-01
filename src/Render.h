/*
Author:         Jakub Marcowski
Description:    Header file for render function
*/

#ifndef RENDER_H
#define RENDER_H

#include "Shape.h"

void render(sf::RenderWindow &w, std::vector<Box *> &boxes, std::vector<Polygon *> &polygons,
            std::vector<Circle *> &circles);

#endif
