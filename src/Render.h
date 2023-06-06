/**
 * @brief Header file for render function.
 *
 * @file Render.h
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef RENDER_H
#define RENDER_H

#include <vector>

#include "../config/Config.h"
#include "Car.h"
#include "Shape.h"
#include "Utility.h"

/**
 * @brief Function for rendering a circle.
 *
 * @param w SFML's RenderWindow.
 * @param circle Pointer to the circle.
 */
void renderCircle(sf::RenderWindow &w, Circle *circle);

/**
 * @brief Function for rendering a circle's debug information.
 *
 * @param w SFML's RenderWindow.
 * @param circle Pointer to the circle.
 */
void renderCircleDebug(sf::RenderWindow &w, Circle *circle);

/**
 * @brief Function for rendering a polygon.
 *
 * @param w SFML's RenderWindow.
 * @param polygon Pointer to the polygon.
 */
void renderPolygon(sf::RenderWindow &w, Polygon *polygon);

/**
 * @brief Function for rendering a polygon's debug information.
 *
 * @param w SFML's RenderWindow.
 * @param polygon Pointer to the polygon.
 */
void renderPolygonDebug(sf::RenderWindow &w, Polygon *polygon);

/**
 * @brief Function for rendering a car.
 *
 * @param w SFML's RenderWindow.
 * @param car Car to be rendered.
 */
void renderCar(sf::RenderWindow &w, Car car);

/**
 * @brief Main render function.
 *
 * @param w SFML's RenderWindow.
 * @param BGs Vector of background sprites.
 * @param ground Vector of ground polygons.
 * @param cars Vector of cars.
 */
void render(sf::RenderWindow &w, const std::vector<sf::Sprite> &BGs, std::vector<Polygon> &ground,
            std::vector<Car> &cars);

#endif
