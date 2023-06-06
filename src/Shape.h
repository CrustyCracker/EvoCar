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

/**
 * @brief Struct representing a box.
 */
struct Box {
    float width{};
    float height{};
    sf::Color color;
    b2Body* body{};
};

/**
 * @brief Struct representing a circle.
 */
struct Circle {
    float radius{};
    sf::Color color;
    b2Body* body{};
};

/**
 * @brief Struct representing a polygon.
 */
struct Polygon {
    std::vector<b2Vec2> vertices;
    sf::Color color;
    b2Body* body;
};

typedef std::shared_ptr<b2World> b2WorldPtr;

/**
 * @brief Creates a box.
 *
 * @param world 2dWorld.
 * @param x X coordinate of the box.
 * @param y Y coordinate of the box.
 * @param width Width of the box.
 * @param height Height of the box.
 * @param density Density of the box.
 * @param friction Friction of the box.
 * @param color Color of the box.
 * @return Box
 */
Box createBox(const b2WorldPtr& world, float x, float y, float width, float height, float density,
              float friction, sf::Color color);

/**
 * @brief Create a Ground object
 * 
 * @param world 2dWorld.
 * @param x X coordinate of the polygon.
 * @param y Y coordinate of the polygon.
 * @param vertices vectors that make up the ground
 * @param color color of the polygon.
 * @return Polygon
 */
Polygon createGround(const b2WorldPtr& world, float x, float y, const std::vector<b2Vec2>& vertices,
                     sf::Color color);

/**
 * @brief Create a Circle object
 * 
 * @param world 2dWorld
 * @param x X coordinate of the circle.
 * @param y Y coordinate of the circle.
 * @param radius radius of the circle.
 * @param density density of the circle.
 * @param friction friction of the circle.
 * @param color color of the circle.
 * @return Circle 
 */
Circle createCircle(const b2WorldPtr& world, float x, float y, float radius, float density,
                    float friction, sf::Color color);

/**
 * @brief Create a Polygon object
 * 
 * @param world 2dWorld.
 * @param x X coordinate of the polygon.
 * @param y Y coordinate of the polygon.
 * @param vertices vectorst that make up the polygon.
 * @param density density of the polygon.
 * @param friction friction of the polygon.
 * @param color color of the polygon.
 * @return Polygon 
 */
Polygon createPolygon(const b2WorldPtr& world, float x, float y, std::vector<b2Vec2> vertices,
                      float density, float friction, sf::Color color);

#endif
