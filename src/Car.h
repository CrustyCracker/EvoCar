/*
Author:         Jakub Marcowski
Description:    Creates a car with a polygon (car's body)
    and two circles (front and back wheels).
*/

#ifndef CAR_H
#define CAR_H
#include "box2d/box2d.h"
#include "Shape.h"

struct Car {
    Polygon* body;
    Circle* frontWheel;
    Circle* backWheel;
    sf::Color bodyColor;
};

struct CarAlt {
    Polygon body;
    Circle frontWheel;
    Circle backWheel;
    sf::Color bodyColor;
};

Car createCar(b2World* world, std::vector<Polygon>* polygons, std::vector<Circle>* circles,
              float carColor[3]);

CarAlt createCarAlt(b2World* world, float x, float y, float carColor[3]);

#endif
