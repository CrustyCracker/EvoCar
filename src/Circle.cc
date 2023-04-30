#include "Circle.h"
/*
Author:
Description:
*/
Circle createCircle(b2World* world, float x, float y, float radius, float density, float friction,
                    sf::Color color) {
    // Body definition
    b2BodyDef boxBodyDef;
    boxBodyDef.position.Set(x / Config::PPM, y / Config::PPM);
    boxBodyDef.type = b2_dynamicBody;

    // Shape definition
    b2CircleShape circleShape;
    circleShape.m_radius = radius / Config::PPM;

    // Fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.shape = &circleShape;

    // Now we have a body for our Box object
    b2Body* boxBody = world->CreateBody(&boxBodyDef);
    // Lastly, assign the fixture
    boxBody->CreateFixture(&fixtureDef);

    return Circle{radius, color, boxBody};
}
