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

void generateGround(b2WorldPtr world, std::vector<Polygon>* boxes, std::vector<Car> cars);

float getNextGroundPartDegree();

Car generateCar(b2WorldPtr world, Chromosome chromosome);

ImVec4 SFMLColorToImVec4(sf::Color color);

b2Vec2 getFurthestCarPos(const std::vector<Car>& cars);

// TODO: Rename this, I beg you
int getIndexOfGroundClosestToLocation(std::vector<Polygon> ground, float x);

void removeCars(const b2WorldPtr& world, std::vector<Car>* cars);

std::filesystem::path getRootDir();

void setIcon(sf::RenderWindow& window);

std::vector<sf::Texture*> loadBGTextures();

sf::Sprite loadBGSprite(sf::Texture* texture, std::vector<Car> cars);

std::vector<sf::Sprite> loadBGSprites(std::vector<sf::Texture*> textures,
                                      const std::vector<Car>& cars);

#endif
