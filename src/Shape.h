/*
Author:         Jakub Marcowski
Description:    This file contains functions for creating Box2D objects.
*/

#ifndef SHAPE_H
#define SHAPE_H

#include "../config/Config.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

struct Box {
    float width;
    float height;
    sf::Color color;
    b2Body* body;
};

struct Circle {
    float radius;
    sf::Color color;
    b2Body* body;
};

struct Polygon {
    std::vector<b2Vec2> vertices;
    sf::Color color;
    b2Body* body;
};

Box createBox(b2World* world, float x, float y, float width, float height, float density,
              float friction, sf::Color color);

/*
This function is used to create a static rectangular body, which will be used as a ground.
*/
Box createGround(b2World* world, float x, float y, float width, float height, sf::Color color);

Circle createCircle(b2World* world, float x, float y, float radius, float density, float friction,
                    sf::Color color);

Polygon createPolygon(b2World* world, float x, float y, std::vector<b2Vec2> vertices, float density,
                      float friction, sf::Color color);

#endif
