#include "Car.h"

/*
Author:         Jakub Marcowski, Mateusz Krakowski
Description:    Creates a car with a polygon (car's body)
    and two circles (front and back wheels).
*/

Car::Car(b2WorldPtr world, float x, float y, std::vector<b2Vec2> vertices, float density, float wheelRadious, sf::Color bodyColor, sf::Color wheelColor) {
    // Create a polygon (octagon)
    body = createPolygon(world, x, y, vertices, density, Config::FRICTION, bodyColor);

    // Create a circle
    frontWheel = createCircle(world, x, y, wheelRadious, density, Config::FRICTION, wheelColor);

    // Create another circle
    backWheel = createCircle(world, x, y, wheelRadious, density, Config::FRICTION, wheelColor);

    b2DistanceJointDef jointDef2;
    jointDef2.bodyA = body.body;
    jointDef2.bodyB = frontWheel.body;
    jointDef2.localAnchorA = vertices[1];
    jointDef2.localAnchorB = vertices[0];
    jointDef2.maxLength = Config::MAX_JOINT_LENGTH;
    jointDef2.collideConnected = false;
    world->CreateJoint(&jointDef2);

    jointDef2.bodyA = body.body;
    jointDef2.bodyB = backWheel.body;
    jointDef2.localAnchorA = vertices[2];
    jointDef2.localAnchorB = vertices[0];
    jointDef2.maxLength = Config::MAX_JOINT_LENGTH;
    jointDef2.collideConnected = false;
    world->CreateJoint(&jointDef2);
}

Polygon* Car::getBody() { return &body; }

Circle* Car::getFrontWheel() { return &frontWheel; }

Circle* Car::getBackWheel() { return &backWheel; }

sf::Color* Car::getBodyColor() { return &bodyColor; }

void Car::setCollisionFilter(b2Filter filter) {
    body.body->GetFixtureList()->SetFilterData(filter);
    frontWheel.body->GetFixtureList()->SetFilterData(filter);
    backWheel.body->GetFixtureList()->SetFilterData(filter);
}
