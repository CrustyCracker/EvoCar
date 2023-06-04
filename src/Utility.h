/*
Author:         Jakub Marcowski, Mateusz Krakowski
Description:    Header for a file containing utility functions.
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <random>
#include <math.h>
#include "imgui.h"
#include "SFML/Graphics.hpp"
#include "../config/MapGenConfig.h"

#include "Car.h"

typedef std::shared_ptr<b2World> b2WorldPtr;

// TODO: think if some of these functions should be moved to other files
// and whether or not some constants should be moved to config

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

void generateGround(b2WorldPtr world, std::vector<Polygon>* boxes, std::vector<Car> cars);

float getNextGroundPartDegree();

Car generateRandomCar(b2WorldPtr world);

ImVec4 SFMLColorToImVec4(sf::Color color);

float getFurthestCarX(std::vector<Car> cars);

#endif
