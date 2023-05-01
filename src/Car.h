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
    Polygon body;
    Circle frontWheel;
    Circle backWheel;
    sf::Color bodyColor;
};

Car createCar(b2World* world, float x, float y, float carColor[3]);

#endif
