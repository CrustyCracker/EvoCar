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

typedef std::shared_ptr<b2World> b2WorldPtr;

class Car {
   private:
    b2WorldPtr world;
    Polygon body;
    Circle frontWheel;
    Circle backWheel;
    std::vector<float> velX;
    std::vector<float> velY;

   public:
    Car(b2WorldPtr world, float x, float y, std::vector<b2Vec2> vertices, float density,
        float wheelRadious, sf::Color bodyColor, sf::Color wheelColor);

    Polygon* getBody();
    Circle* getFrontWheel();
    Circle* getBackWheel();
    std::vector<float>* getVelX();
    std::vector<float>* getVelY();
    sf::Color getBodyColor();
    b2Vec2 getVelocityVec();
    float getVelocity();
    void setCollisionFilter(b2Filter filter);
};

std::vector<b2Vec2> createVertices(std::vector<float> lengths, std::vector<float> angles);

#endif
