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

class Car {
   private:
    b2WorldPtr world_;
    Polygon body_;
    Circle frontWheel_;
    Circle backWheel_;
    std::vector<float> velX_;
    std::vector<float> velY_;

   public:
    Car(const b2WorldPtr& world, float x, float y, const Chromosome& chromosome,
        sf::Color bodyColor, sf::Color wheelColor);

    Polygon* getBody();
    Circle* getFrontWheel();
    Circle* getBackWheel();
    float getPosX() const;
    float getPosY() const;
    std::vector<float>* getVelX();
    std::vector<float>* getVelY();
    sf::Color getBodyColor() const;
    b2Vec2 getVelocityVec() const;
    float getVelocity() const;
    void setCollisionFilter(b2Filter filter) const;
};

std::vector<b2Vec2> createVertices(std::vector<float> lengths);

#endif
