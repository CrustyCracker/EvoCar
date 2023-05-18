/*
Author:         Jakub Marcowski
Description:    Creates a car with a polygon (car's body)
    and two circles (front and back wheels).
*/

#ifndef CAR_H
#define CAR_H
#include "box2d/box2d.h"
#include "Shape.h"
#include "../config/Config.h"

typedef std::shared_ptr<b2World> b2WorldPtr;
class Car {
   private:
    b2WorldPtr world;
    Polygon body;
    Circle frontWheel;
    Circle backWheel;
    sf::Color bodyColor;

   public:
    Car(b2WorldPtr world, float x, float y, std::vector<b2Vec2> vertices, float density,
        float wheelRadious, sf::Color bodyColor, sf::Color wheelColor);

    Polygon* getBody();
    Circle* getFrontWheel();
    Circle* getBackWheel();
    sf::Color* getBodyColor();
    void setCollisionFilter(b2Filter filter);
};

#endif
