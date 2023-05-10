/*
Author:         Jakub Marcowski
Description:    Header file for render function
*/

#ifndef RENDER_H
#define RENDER_H

#include "Car.h"
#include "../config/Config.h"
#include "Shape.h"

void renderBox(sf::RenderWindow &w, Box &box);

void renderCircle(sf::RenderWindow &w, Circle *circle);

void renderCircleDebug(sf::RenderWindow &w, Circle *circle);

void renderPolygon(sf::RenderWindow &w, Polygon *polygon);

void renderPolygonDebug(sf::RenderWindow &w, Polygon *polygon);

void renderCar(sf::RenderWindow &w, Car *car);

void render(sf::RenderWindow &w, std::vector<Box> &boxes, std::vector<Car *> &cars);

#endif
