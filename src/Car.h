/*
Author:
Description:
*/

#ifndef CAR_H
#define CAR_H
#include "box2d/box2d.h"
#include "Shape.h"

Polygon createCar(b2World* world, std::vector<Polygon>* polygons, std::vector<Circle>* circles,
                  float carColor[3]);

#endif
