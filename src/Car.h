#ifndef CAR_H
#define CAR_H

#include "Circle.h"
#include "Polygon.h"
#include "box2d/box2d.h"

Polygon createCar(b2World* world, std::vector<Polygon>* polygons, std::vector<Circle>* circles,
                  float carColor[3]);

#endif
