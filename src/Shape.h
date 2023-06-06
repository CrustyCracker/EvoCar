/**
 * @brief Header file for functions for creating Box2D objects.
 *
 * @file Shape.h
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <memory>

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

#include "../config/CarConfig.h"
#include "../config/Config.h"

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

typedef std::shared_ptr<b2World> b2WorldPtr;

Box createBox(b2WorldPtr world, float x, float y, float width, float height, float density,
              float friction, sf::Color color);

Polygon createGround(b2WorldPtr world, float x, float y, const std::vector<b2Vec2>& vertices,
                     sf::Color color);

Circle createCircle(b2WorldPtr world, float x, float y, float radius, float density, float friction,
                    sf::Color color);

Polygon createPolygon(b2WorldPtr world, float x, float y, std::vector<b2Vec2> vertices,
                      float density, float friction, sf::Color color);

#endif
