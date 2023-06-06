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

/**
 * @brief Simplified air drag.
 * @param car Car to apply air resistance to.
 */
void applyAirResistance(Car car);

/**
 * @brief Simplified air drag.
 * @param world A shared pointer to the box2d world.
 * @param groundVector A vector of ground polygons.
 * @param cars A vector of cars.
 */
void generateGround(const b2WorldPtr& world, std::vector<Polygon>* groundVector,
                    const std::vector<Car>& cars);

/**
 * @brief Get the angle of the next ground part.
 * @return float
 */
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

/**
 * @brief Get the Root Dir object
 *
 * @return std::filesystem::path to the root directory
 */
std::filesystem::path getRootDir();

/**
 * @brief Sets the icon of the window.
 *
 * @param window
 */
void setIcon(sf::RenderWindow& window);

/**
 * @brief Loads the textures for the background and returns them in a vector.
 *
 * @return std::vector<sf::Texture*>
 */
std::vector<sf::Texture*> loadBGTextures();

/**
 * @brief Loads the sprite for the background.
 *
 * @param texture
 * @param cars
 * @return sf::Sprite
 */
sf::Sprite loadBGSprite(sf::Texture* texture, const std::vector<Car>& cars);

/**
 * @brief Loads the sprites for the background.
 *
 * @param textures
 * @param cars
 * @return std::vector<sf::Sprite>
 */
std::vector<sf::Sprite> loadBGSprites(std::vector<sf::Texture*> textures,
                                      const std::vector<Car>& cars);

#endif  // UTILITY_H
