#ifndef POLYGON_H
#define POLYGON_H

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "../config/Config.h"

/*
Author:
Description:
*/
struct Polygon {
    std::vector<b2Vec2> vertices;
    sf::Color color;
    b2Body* body;
};

Polygon createPolygon(b2World* world, float x, float y, std::vector<b2Vec2> vertices, float density,
                      float friction, sf::Color color);

#endif