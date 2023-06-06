/**
 * @brief Header file for render function.
 *
 * @file Render.h
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef RENDER_H
#define RENDER_H

#include "../config/Config.h"
#include "Car.h"
#include "Shape.h"
#include "Utility.h"

void renderBox(sf::RenderWindow &w, Box &box);

void renderCircle(sf::RenderWindow &w, Circle *circle);

void renderCircleDebug(sf::RenderWindow &w, Circle *circle);

void renderPolygon(sf::RenderWindow &w, Polygon *polygon);

void renderPolygonDebug(sf::RenderWindow &w, Polygon *polygon);

void renderCar(sf::RenderWindow &w, Car car);

void render(sf::RenderWindow &w, sf::Sprite bg, std::vector<Polygon> &ground,
            std::vector<Car> &cars);

#endif
