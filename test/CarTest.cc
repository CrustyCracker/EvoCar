/**
 * @brief This file contains tests for functions from src/Car.h.
 *
 * @file CarTest.cc
 * @author Mateusz Krakowski
 * @date 2023-06-06
 */

#include <gtest/gtest.h>

#include "../src/Car.h"
#include "../src/EvolutionaryAlgorithm.h"
#include "../config/EvolutionaryAlgorithmConfig.h"

TEST(CreateCarTest, BasicTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f, width = 10.0f, height = 20.0f, density = 1.0f, friction = 0.5f;
    sf::Color bodyColor = sf::Color::Red;
    sf::Color wheelColor = sf::Color::Blue;

    EvolutionaryAlgorithm ea = EvolutionaryAlgorithm(EvolutionaryAlgorithmConfig::POPULATION_SIZE);
    Chromosome chromosome = ea.getPopulation()[0];
    Car car = createCar(world, x, y, chromosome, bodyColor, wheelColor);

    EXPECT_EQ(car.getPosX(), x);
    EXPECT_EQ(car.getPosY(), y);
    EXPECT_EQ(car.getBodyColor, bodyColor);
}
