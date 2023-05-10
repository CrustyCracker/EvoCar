#include "Shape.h"

/*
Author:         Jakub Marcowski
Description:    This file contains functions for creating Box2D objects.
*/

Box createBox(b2World* world, float x, float y, float width, float height, float density,
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

Box createGround(b2World* world, float x, float y, float width, float height, sf::Color color) {
    // Argument validation
    if (width <= 0.0f) {
        throw std::invalid_argument("Invalid width parameter");
    } else if (height <= 0.0f) {
        throw std::invalid_argument("Invalid height parameter");
    }

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x / Config::PPM, y / Config::PPM);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(width / 2 / Config::PPM, height / 2 / Config::PPM);

    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    // For a static body, we don't need a custom fixture definition, this will do:
    groundBody->CreateFixture(&groundBox, 0.0f);

    return Box{width, height, color, groundBody};
}

Circle createCircle(b2World* world, float x, float y, float radius, float density, float friction,
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

Polygon createPolygon(b2World* world, float x, float y, std::vector<b2Vec2> vertices, float density,
                      float friction, sf::Color color) {
    // Argument validation
    if (vertices.size() < 3 || vertices.size() > Config::CAR_VERTICES) {
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

    return Polygon{vertices, color, boxBody};
}
