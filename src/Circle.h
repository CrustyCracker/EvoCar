#ifndef CIRCLE_H
#define CIRCLE_H

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "../config/Config.h"

/*
Author:
Description:
*/
struct Circle {
    float radius;
    sf::Color color;
    b2Body* body;
};

Circle createCircle(b2World* world, float x, float y, float radius, float density, float friction,
                    sf::Color color);

#endif
