/**
 * @brief Header file for the Car class.
 *
 * @file Car.h
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef CAR_H
#define CAR_H

#include <numeric>

#include "box2d/box2d.h"

#include "../config/Config.h"
#include "../config/CarConfig.h"
#include "Shape.h"
#include "EvolutionaryAlgorithm.h"

typedef std::shared_ptr<b2World> b2WorldPtr;

/**
 * @brief Class representing a car.
 */
class Car {
   private:
    b2WorldPtr world_;
    Polygon body_;
    Circle frontWheel_;
    Circle backWheel_;
    std::vector<float> velX_;
    std::vector<float> velY_;
    std::vector<float> posX_;
    std::vector<float> posY_;

   public:
    /**
     * @brief Construct a new Car object.
     *
     * @param world A shared pointer to the Box2D world.
     * @param x X coordinate of the car's center.
     * @param y Y coordinate of the car's center.
     * @param chromosome Genome of the car.
     * @param bodyColor Color of the car's body.
     * @param wheelColor Color of the car's wheels.
     */
    Car(const b2WorldPtr& world, float x, float y, const Chromosome& chromosome,
        sf::Color bodyColor, sf::Color wheelColor);

    /**
     * @brief Get the car's body (polygon).
     *
     * @return Polygon* Pointer to the car's body.
     */
    Polygon* getBody();

    /**
     * @brief Get the car's front wheel.
     *
     * @return Circle* Pointer to the car's front wheel.
     */
    Circle* getFrontWheel();

    /**
     * @brief Get the car's front wheel.
     *
     * @return Circle* Pointer to the car's back wheel.
     */
    Circle* getBackWheel();

    /**
     * @brief Get the car's X position.
     *
     * @return float X position.
     */
    float getPosX() const;

    /**
     * @brief Get the car's X position.
     *
     * @return float Y position.
     */
    float getPosY() const;

    /**
     * @brief Get the object holding car's data for X axis in the velocity graph.
     *
     * @return std::vector<float>* Pointer to the vector.
     */
    std::vector<float>* getVelX();

    /**
     * @brief Get the object holding car's data for Y axis in the velocity graph.
     *
     * @return std::vector<float>* Pointer to the vector.
     */
    std::vector<float>* getVelY();

    /**
     * @brief Get the object holding car's data for X axis in the position graph.
     *
     * @return std::vector<float>* Pointer to the vector.
     */
    std::vector<float>* getPosXVec();

    /**
     * @brief Get the object holding car's data for Y axis in the position graph.
     *
     * @return std::vector<float>* Pointer to the vector.
     */
    std::vector<float>* getPosYVec();

    /**
     * @brief Get the color of the car's body.
     *
     * @return sf::Color Color of the car's body.
     */
    sf::Color getBodyColor() const;

    /**
     * @brief Get the b2Vec2 value of car's velocity.
     *
     * @return b2Vec2 Velocity vector.
     */
    b2Vec2 getVelocityVec() const;

    /**
     * @brief Get the value of car's speed.
     *
     * @return float Speed.
     */
    float getVelocity() const;

    /**
     * @brief Set the collision filter so that cars pass through each-other.
     *
     * @param filter Collision filter.
     */
    void setCollisionFilter(b2Filter filter) const;
};

/**
 * @brief Create a vector of points for a polygon.
 *
 * @param lengths Vector of lengths from the center of the polygon to the vertices.
 * @return std::vector<b2Vec2> Vector of vertices.
 */
std::vector<b2Vec2> createVertices(std::vector<float> lengths);

#endif
