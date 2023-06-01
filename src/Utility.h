/*
Author:         Jakub Marcowski
Description:    -
*/

#ifndef UTILITY_H
#define UTILITY_H

#include "Car.h"

typedef std::shared_ptr<b2World> b2WorldPtr;

/*
simplified air drag

F = V^2 * k
k ≈ 1/2 * ρ * A * C_d ≈ 3.4
ρ = 1.293 kg/m^3
A = ? (let's assume 5 m^2)
C_d = ? (let's assume 1.05)

F = 3.4 * V^2
*/
void applyAirResistance(Car car);

void generateGround(b2WorldPtr world, std::vector<Box> *boxes, std::vector<Car> cars);

#endif
