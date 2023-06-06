/**
 * @brief This file contains tests for functions from src/Shape.h.
 *
 * @file ShapeTest.cc
 * @author Mateusz Krakowski
 * @date 2023-06-06
 */

#include <gtest/gtest.h>
#include "../src/Shape.h"

TEST(CreateBoxTest, BasicTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f, width = 10.0f, height = 20.0f, density = 1.0f, friction = 0.5f;
    sf::Color color = sf::Color::Red;

    Box box = createBox(world, x, y, width, height, density, friction, color);

    EXPECT_EQ(box.body->GetPosition().x, x / Config::PPM);
    EXPECT_EQ(box.body->GetPosition().y, y / Config::PPM);
    EXPECT_EQ(box.width, width);
    EXPECT_EQ(box.height, height);
    EXPECT_EQ(box.color, color);
    EXPECT_EQ(box.body->GetFixtureList()->GetDensity(), density);
    EXPECT_EQ(box.body->GetFixtureList()->GetFriction(), friction);
}

TEST(CreateBoxTest, InvalidWidthTest) {
    // Test with invalid input (negative width and height)
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f, width = -10.0f, height = 10.0f, density = 1.0f, friction = 0.5f;
    sf::Color color = sf::Color::Red;

    ASSERT_THROW(createBox(world, x, y, width, height, density, friction, color),
                 std::invalid_argument);
}

TEST(CreateBoxTest, InvalidHeightTest) {
    // Test with invalid input (negative width and height)
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f, width = 10.0f, height = 0.0f, density = 1.0f, friction = 0.5f;
    sf::Color color = sf::Color::Red;

    ASSERT_THROW(createBox(world, x, y, width, height, density, friction, color),
                 std::invalid_argument);
}

TEST(CreateBoxTest, InvalidDensityTest) {
    // Test with invalid input (negative width and height)
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 1.0f, y = 1.0f, width = 10.0f, height = 1.0f, density = -1.0f, friction = 0.5f;
    sf::Color color = sf::Color::Red;

    ASSERT_THROW(createBox(world, x, y, width, height, density, friction, color),
                 std::invalid_argument);
}

TEST(CreateBoxTest, InvalidFrictionTest) {
    // Test with invalid input (negative width and height)
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 1.0f, y = 1.0f, width = 10.0f, height = 5.0f, density = 2.0f, friction = 0.0f;
    sf::Color color = sf::Color::Red;

    ASSERT_THROW(createBox(world, x, y, width, height, density, friction, color),
                 std::invalid_argument);
}

TEST(CreateGroundTest, BasicTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 42.0f, y = 42.0f;
    std::vector<b2Vec2> vertices = {b2Vec2(-25.0f, -5.0f), b2Vec2(25.0f, -5.0f),
                                    b2Vec2(25.0f, 5.0f), b2Vec2(-25.0f, 5.0f)};
    sf::Color color = sf::Color::Blue;

    ASSERT_NO_THROW(Polygon ground = createGround(world, x, y, vertices, color));

    Polygon ground = createGround(world, x, y, vertices, color);
    ASSERT_EQ(ground.vertices, vertices);
    ASSERT_EQ(ground.color, color);
    ASSERT_EQ(ground.body->GetType(), b2_staticBody);
    ASSERT_EQ(ground.body->GetFixtureList()->GetDensity(), 0.0f);
}

TEST(CreateGroundTest, InvalidVerticesTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 42.0f, y = 42.0f;
    std::vector<b2Vec2> invalidVertices;  // Empty vertices

    sf::Color color = sf::Color::Blue;

    ASSERT_THROW(createGround(world, x, y, invalidVertices, color), std::invalid_argument);
}

TEST(CreateCircleTest, BasicTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 10.0f, y = 20.0f, radius = 2.0f, density = 1.0f, friction = 0.5f;
    sf::Color color(255, 255, 0);

    Circle circle = createCircle(world, x, y, radius, density, friction, color);

    ASSERT_EQ(circle.radius, radius);
    ASSERT_EQ(circle.color, color);
    ASSERT_EQ(circle.body->GetType(), b2_dynamicBody);
    ASSERT_EQ(circle.body->GetPosition(), b2Vec2(x / Config::PPM, y / Config::PPM));
    ASSERT_EQ(circle.body->GetFixtureList()->GetDensity(), density);
    ASSERT_EQ(circle.body->GetFixtureList()->GetFriction(), friction);
}

TEST(CreateCircleTest, InvalidRadiusTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 10.0f, y = 20.0f, radius = 0.0f, density = 1.0f, friction = 0.5f;
    sf::Color color(255, 255, 0);

    ASSERT_THROW(createCircle(world, x, y, radius, density, friction, color),
                 std::invalid_argument);
}

TEST(CreateCircleTest, InvalidDensityTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 10.0f, y = 20.0f, radius = 2.0f, density = -1.0f, friction = 0.5f;
    sf::Color color(255, 255, 0);

    ASSERT_THROW(createCircle(world, x, y, radius, density, friction, color),
                 std::invalid_argument);
}

TEST(CreateCircleTest, InvalidFrictionTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 10.0f, y = 20.0f, radius = 2.0f, density = 1.0f, friction = -0.5f;
    sf::Color color(255, 255, 0);

    ASSERT_THROW(createCircle(world, x, y, radius, density, friction, color),
                 std::invalid_argument);
}

TEST(CreatePolygonTest, BasicTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f, density = 1.0f, friction = 0.5f;
    std::vector<b2Vec2> vertices = {b2Vec2(-1.0f, -1.0f), b2Vec2(1.0f, -1.0f), b2Vec2(0.0f, 1.0f)};
    sf::Color color = sf::Color::Red;
    Polygon polygon = createPolygon(world, x, y, vertices, density, friction, color);

    EXPECT_NE(nullptr, polygon.body);

    ASSERT_EQ(polygon.body->GetPosition(), b2Vec2(x / Config::PPM, y / Config::PPM));

    std::shared_ptr<const b2Fixture> fixture(polygon.body->GetFixtureList(),
                                             [](const b2Fixture* f) {});
    ASSERT_NE(nullptr, fixture);
    std::shared_ptr<const b2PolygonShape> shape(
        dynamic_cast<const b2PolygonShape*>(fixture->GetShape()), [](const b2PolygonShape* s) {});
    ASSERT_NE(nullptr, shape);

    EXPECT_EQ(density, fixture->GetDensity());
    EXPECT_EQ(friction, fixture->GetFriction());
}

TEST(CreatePolygonTest, EmptyVerticesTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f, density = 1.0f, friction = 0.5f;
    std::vector<b2Vec2> vertices = {};
    sf::Color color = sf::Color::Red;
    ASSERT_THROW(createPolygon(world, x, y, vertices, density, friction, color);
                 , std::invalid_argument);
}

TEST(CreatePolygonTest, TooMuchVerticesTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f, density = 1.0f, friction = 0.5f;
    std::vector<b2Vec2> vertices = {b2Vec2(-1.0f, -1.0f), b2Vec2(1.0f, -1.0f), b2Vec2(0.0f, 1.0f),
                                    b2Vec2(-1.0f, -1.0f), b2Vec2(1.0f, -1.0f), b2Vec2(0.0f, 1.0f),
                                    b2Vec2(-1.0f, -1.0f), b2Vec2(1.0f, -1.0f), b2Vec2(0.0f, 1.0f)};
    sf::Color color = sf::Color::Red;
    ASSERT_THROW(createPolygon(world, x, y, vertices, density, friction, color);
                 , std::invalid_argument);
}

TEST(CreatePolygonTest, InvalidDensityTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f, density = 0.0f, friction = 0.5f;
    std::vector<b2Vec2> vertices = {b2Vec2(-1.0f, -1.0f), b2Vec2(1.0f, -1.0f), b2Vec2(0.0f, 1.0f),
                                    b2Vec2(-1.0f, -1.0f), b2Vec2(1.0f, -1.0f), b2Vec2(0.0f, 1.0f),
                                    b2Vec2(-1.0f, -1.0f), b2Vec2(1.0f, -1.0f)};
    sf::Color color = sf::Color::Red;
    ASSERT_THROW(createPolygon(world, x, y, vertices, density, friction, color);
                 , std::invalid_argument);
}

TEST(CreatePolygonTest, InvalidFrictionTest) {
    b2WorldPtr world = std::make_shared<b2World>(b2Vec2(0.0f, Config::GRAVITATIONAL_ACCELERATION));
    float x = 0.0f, y = 0.0f, density = 1.0f, friction = -0.5f;
    std::vector<b2Vec2> vertices = {b2Vec2(-1.0f, -1.0f), b2Vec2(1.0f, -1.0f), b2Vec2(0.0f, 1.0f),
                                    b2Vec2(-1.0f, -1.0f), b2Vec2(1.0f, -1.0f), b2Vec2(0.0f, 1.0f),
                                    b2Vec2(-1.0f, -1.0f), b2Vec2(1.0f, -1.0f)};
    sf::Color color = sf::Color::Red;
    ASSERT_THROW(createPolygon(world, x, y, vertices, density, friction, color);
                 , std::invalid_argument);
}