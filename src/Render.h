#ifndef RENDER_H
#define RENDER_H

#include "Box.h"
#include "Circle.h"
#include "Polygon.h"

void render(sf::RenderWindow &w, std::vector<Box> &boxes, std::vector<Polygon> &polygons,
            std::vector<Circle> &circles);

#endif
