#ifndef RENDER_H
#define RENDER_H

#include "box.h"
#include "circle.h"
#include "polygon.h"

void render(sf::RenderWindow &w, std::vector<Box> &boxes, std::vector<Polygon> &polygons,
            std::vector<Circle> &circles);

#endif
