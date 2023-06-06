/**
 * @brief Header for a file containing utility functions.
 *
 * @file Utility.h
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef UTILITY_H
#define UTILITY_H

#include <random>
#include <math.h>

#include "imgui.h"
#include "SFML/Graphics.hpp"
#include "EvolutionaryAlgorithm.h"

#include "../config/MapGenConfig.h"
#include "Car.h"

typedef std::shared_ptr<b2World> b2WorldPtr;

// TODO: think if some of these functions should be moved to other files
// and whether or not some constants should be moved to config

/**
 * @brief Simplified air drag.
 * @param car Car to apply air resistance to.
 * @return void
 */
void applyAirResistance(Car car);

void generateGround(b2WorldPtr world, std::vector<Polygon>* boxes, std::vector<Car> cars);

float getNextGroundPartDegree();

Car generateCar(b2WorldPtr world, Chromosome chromosome);

ImVec4 SFMLColorToImVec4(sf::Color color);

float getFurthestCarX(std::vector<Car> cars);

// TODO: Rename this, I beg you
int getIndexOfGroundClosestToLocation(std::vector<Polygon> ground, float x);

void removeCars(b2WorldPtr world, std::vector<Car>* cars);

#endif
