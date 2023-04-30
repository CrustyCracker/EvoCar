/*
Author:         Jakub Marcowski
Description:    This file contains the render function, which is responsible
    for rendering all the shapes in the world.
*/

#ifndef RENDER_H
#define RENDER_H

#include "Shape.h"

void render(sf::RenderWindow &w, std::vector<Box> &boxes, std::vector<Polygon> &polygons,
            std::vector<Circle> &circles);

#endif
