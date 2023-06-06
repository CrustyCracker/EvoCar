/**
 * @brief Header for a file containing utility functions.
 *
 * @file Utility.h
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef UTILITY_H
#define UTILITY_H

#include <filesystem>
#include <cmath>
#include <random>
#include <vector>

#include "box2d/box2d.h"
#include "imgui.h"
#include "SFML/Graphics.hpp"
#include "EvolutionaryAlgorithm.h"

#include "../config/Config.h"
#include "../config/MapGenConfig.h"
#include "Car.h"

typedef std::shared_ptr<b2World> b2WorldPtr;

// TODO: think if some of these functions should be moved to other files
// and whether or not some constants should be moved to config

/**
 * @brief Simplified air drag.
 * @param car Car to apply air resistance to.
 */
void applyAirResistance(Car car);

void generateGround(const b2WorldPtr& world, std::vector<Polygon>* boxes,
                    const std::vector<Car>& cars);

float getNextGroundPartDegree();

Car generateCar(const b2WorldPtr& world, const Chromosome& chromosome);

/**
 * @brief Transforms a SFML color into an ImGUI color.
 *
 * @param color SFML color.
 * @return ImVec4 ImGUI color.
 */
ImVec4 SFMLColorToImVec4(sf::Color color);

/**
 * @brief Returns the b2Vec2 position of the car
 * that is the furthest from the starting point.
 *
 * @param cars Vector of cars.
 * @return b2Vec2 Position of the furthest car.
 */
b2Vec2 getFurthestCarPos(const std::vector<Car>& cars);

/**
 * @brief "Get Index Of Ground Closest To Location"
 * - returns the index of the ground element that is the closest to the given
 * location.
 *
 * @param cars Vector of cars.
 * @return int Index of the ground element.
 */
int getIdxOfGrndClstToLoc(std::vector<Polygon> ground, float x);

/**
 * @brief Deletes all cars from the world and the Car vector.
 *
 * @param world A shared pointer to the box2d world.
 * @param cars A vector of cars.
 */
void removeCars(const b2WorldPtr& world, std::vector<Car>* cars);

std::filesystem::path getRootDir();

void setIcon(sf::RenderWindow& window);

std::vector<sf::Texture*> loadBGTextures();

sf::Sprite loadBGSprite(sf::Texture* texture, const std::vector<Car>& cars);

std::vector<sf::Sprite> loadBGSprites(std::vector<sf::Texture*> textures,
                                      const std::vector<Car>& cars);

#endif  // UTILITY_H
