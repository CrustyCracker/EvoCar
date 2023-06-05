/*
Author:         Jakub Marcowski, Mateusz Krakowski
Description:    Header file for the Car class.
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

    bool isAlive_ = true;

   public:
    Car(b2WorldPtr world, float x, float y, Chromosome chormosome, sf::Color bodyColor,
        sf::Color wheelColor);

    Polygon* getBody();
    Circle* getFrontWheel();
    Circle* getBackWheel();
    float getPosX();
    float getPosY();
    std::vector<float>* getVelX();
    std::vector<float>* getVelY();
    sf::Color getBodyColor();
    b2Vec2 getVelocityVec();
    float getVelocity();
    void setCollisionFilter(b2Filter filter);
};

std::vector<b2Vec2> createVertices(std::vector<float> lengths);

#endif
