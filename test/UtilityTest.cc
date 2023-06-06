/**
 * @brief This file contains tests for functions from src/Car.h.
 *
 * @file CarTest.cc
 * @author Mateusz Krakowski
 * @date 2023-06-03
 */

#include <gtest/gtest.h>

#include "../src/Utility.h"
#include "../src/Car.h"
#include "../src/EvolutionaryAlgorithm.h"

TEST(UtilityTest, applyAirResistanceTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f;
    sf::Color bodyColor = sf::Color::Red;
    sf::Color wheelColor = sf::Color::Blue;

    EvolutionaryAlgorithm ea = EvolutionaryAlgorithm(EvolutionaryAlgorithmConfig::POPULATION_SIZE);
    Chromosome chromosome = ea.getPopulation()[0];
    Car car = Car(world, x, y, chromosome, bodyColor, wheelColor);

    EXPECT_NO_THROW(applyAirResistance(car));
}

TEST(UtilityTest, generateGroundTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f;
    sf::Color bodyColor = sf::Color::Red;
    sf::Color wheelColor = sf::Color::Blue;

    EvolutionaryAlgorithm ea = EvolutionaryAlgorithm(EvolutionaryAlgorithmConfig::POPULATION_SIZE);
    Chromosome chromosome = ea.getPopulation()[0];
    std::vector<Car> cars;

    Car car = Car(world, x, y, chromosome, bodyColor, wheelColor);
    cars.push_back(car);

    std::vector<Polygon> groundVector = {createGround(std::move(world), MapGenConfig::GROUND_STARTING_X,
                                                      MapGenConfig::GROUND_STARTING_Y,
                                                      MapGenConfig::GROUND_STARTING_VERTICES,
                                                      sf::Color(18, 36, 35))};

    EXPECT_NO_THROW(generateGround(world, &groundVector, cars));

    EXPECT_EQ(groundVector.size(), 2);
}

TEST(UtilityTest, getNextGroundPartDegreeTest) {
    EXPECT_NO_THROW(getNextGroundPartDegree());
}

TEST(UtilityTest, generateCarTest){
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f;
    sf::Color bodyColor = sf::Color::Red;
    sf::Color wheelColor = sf::Color::Blue;

    EvolutionaryAlgorithm ea = EvolutionaryAlgorithm(EvolutionaryAlgorithmConfig::POPULATION_SIZE);
    Chromosome chromosome = ea.getPopulation()[0];

    EXPECT_NO_THROW(generateCar(world, chromosome));
}

TEST(UtilityTest, getFurthestCarXTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f;
    sf::Color bodyColor = sf::Color::Red;
    sf::Color wheelColor = sf::Color::Blue;

    EvolutionaryAlgorithm ea = EvolutionaryAlgorithm(EvolutionaryAlgorithmConfig::POPULATION_SIZE);
    Chromosome chromosome = ea.getPopulation()[0];
    std::vector<Car> cars;

    Car car = Car(world, x, y, chromosome, bodyColor, wheelColor);
    cars.push_back(car);

    EXPECT_NO_THROW(getFurthestCarX(cars));
    EXPECT_EQ(getFurthestCarX(cars), x);
}

TEST(UtilityTest, SFMLColorToImVec4){
    sf::Color color = sf::Color::Red;
    ImVec4 imVec4 = SFMLColorToImVec4(color);

    EXPECT_EQ(imVec4.x, 1.0f);
    EXPECT_EQ(imVec4.y, 0.0f);
    EXPECT_EQ(imVec4.z, 0.0f);
    EXPECT_EQ(imVec4.w, 1.0f);
}

TEST(UtilityTest, getIndexOfGroundClosestToLocationTest){
    std::vector<Polygon> groundVector = {createGround(std::move(world), MapGenConfig::GROUND_STARTING_X,
                                                      MapGenConfig::GROUND_STARTING_Y,
                                                      MapGenConfig::GROUND_STARTING_VERTICES,
                                                      sf::Color(18, 36, 35))};

    EXPECT_NO_THROW(getIndexOfGroundClosestToLocation(groundVector, 0.0f));
    EXPECT_EQ(getIndexOfGroundClosestToLocation(groundVector, 0.0f), 0);
}

TEST(UtilityTest, removeCarsTest){
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f;
    sf::Color bodyColor = sf::Color::Red;
    sf::Color wheelColor = sf::Color::Blue;

    EvolutionaryAlgorithm ea = EvolutionaryAlgorithm(EvolutionaryAlgorithmConfig::POPULATION_SIZE);
    Chromosome chromosome = ea.getPopulation()[0];
    std::vector<Car> cars;

    Car car = Car(world, x, y, chromosome, bodyColor, wheelColor);
    cars.push_back(car);

    EXPECT_NO_THROW(removeCars(cars));
    EXPECT_EQ(cars.size(), 0);
}

TEST(UtilityTest, getRootDirTest){
    EXPECT_NO_THROW(getRootDir());
}

TEST(UtilityTest, setIconTest){
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    EXPECT_NO_THROW(setIcon(window));
}

TEST(UtilityTest, loadBGSpritesTEST){
    EXPECT_NO_THROW(loadBGSprites());
}

TEST(UtilityTest, loadBGSpriteTest){
    EXPECT_NO_THROW(loadBGSprite());
}

TEST(UtilityTest, loadFontTest){
    EXPECT_NO_THROW(loadFont());
}
