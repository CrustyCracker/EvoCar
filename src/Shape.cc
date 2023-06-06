/**
 * @brief This file contains functions for creating Box2D objects.
 *
 * @file Shape.cc
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#include "Shape.h"

Box createBox(b2WorldPtr world, float x, float y, float width, float height, float density,
              float friction, sf::Color color) {
    // Argument validation
    if (width <= 0) {
        throw std::invalid_argument("Invalid width parameter");
    } else if (height <= 0.0f) {
        throw std::invalid_argument("Invalid height parameter");
    } else if (density <= 0.0f) {
        throw std::invalid_argument("Invalid density parameter");
    } else if (friction <= 0.0f) {
        throw std::invalid_argument("Invalid friction parameter");
    }
    // Body definition
    b2BodyDef boxBodyDef;
    boxBodyDef.position.Set(x / Config::PPM, y / Config::PPM);
    boxBodyDef.type = b2_dynamicBody;

    // Shape definition
    b2PolygonShape boxShape;
    boxShape.SetAsBox(width / 2 / Config::PPM, height / 2 / Config::PPM);

    // Fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.shape = &boxShape;

    // Now we have a body for our Box object
    b2Body* boxBody = world->CreateBody(&boxBodyDef);
    // Lastly, assign the fixture
    boxBody->CreateFixture(&fixtureDef);

    return Box{width, height, color, boxBody};
}

Polygon createGround(b2WorldPtr world, float x, float y, const std::vector<b2Vec2>& vertices,
                     sf::Color color) {
    // Argument validation
    if (vertices.size() < 3) {
        throw std::invalid_argument("Invalid number of vertices");
    }

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x / Config::PPM, y / Config::PPM);

    b2PolygonShape groundPolygon;
    groundPolygon.Set(vertices.data(), static_cast<int32>(vertices.size()));

    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    groundBody->CreateFixture(&groundPolygon, 0.0f);

    return Polygon{vertices, color, groundBody};
}

Circle createCircle(b2WorldPtr world, float x, float y, float radius, float density, float friction,
                    sf::Color color) {
    // Argument validation
    if (radius <= 0.0f) {
        throw std::invalid_argument("Invalid width parameter");
    } else if (density <= 0.0f) {
        throw std::invalid_argument("Invalid density parameter");
    } else if (friction <= 0.0f) {
        throw std::invalid_argument("Invalid friction parameter");
    }

    b2BodyDef boxBodyDef;
    boxBodyDef.position.Set(x / Config::PPM, y / Config::PPM);
    boxBodyDef.type = b2_dynamicBody;

    b2CircleShape circleShape;
    circleShape.m_radius = radius / Config::PPM;

    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.shape = &circleShape;

    b2Body* boxBody = world->CreateBody(&boxBodyDef);

    boxBody->CreateFixture(&fixtureDef);

    return Circle{radius, color, boxBody};
}

Polygon createPolygon(b2WorldPtr world, float x, float y, std::vector<b2Vec2> vertices,
                      float density, float friction, sf::Color color) {
    // Argument validation
    if (vertices.size() < 3 || vertices.size() > CarConfig::CAR_VERTICES) {
        throw std::invalid_argument("Invalid vertices size");
    } else if (density <= 0.0f) {
        throw std::invalid_argument("Invalid density parameter");
    } else if (friction <= 0.0f) {
        throw std::invalid_argument("Invalid friction parameter");
    }
    b2BodyDef boxBodyDef;
    boxBodyDef.position.Set(x / Config::PPM, y / Config::PPM);
    boxBodyDef.type = b2_dynamicBody;

    b2PolygonShape boxShape;
    boxShape.Set(vertices.data(), vertices.size());

    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.shape = &boxShape;

    b2Body* boxBody = world->CreateBody(&boxBodyDef);

    boxBody->CreateFixture(&fixtureDef);

    // create a Polygon object with a shared pointer to the b2Body
    return Polygon{vertices, color, boxBody};
}
