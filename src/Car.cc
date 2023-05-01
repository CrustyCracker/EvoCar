#include "Car.h"

/*
Author:         Jakub Marcowski
Description:    Creates a car with a polygon (car's body)
    and two circles (front and back wheels).
*/

Car::Car(b2World* world, float x, float y, float carColor[3]) {
    bodyColor =
        sf::Color((int)(carColor[0] * 255), (int)(carColor[1] * 255), (int)(carColor[2] * 255));

    // Create a polygon (octagon)
    std::vector<b2Vec2> vertices;
    vertices.push_back(b2Vec2(0, 0));
    vertices.push_back(b2Vec2(1, -1));
    vertices.push_back(b2Vec2(4, -1));
    vertices.push_back(b2Vec2(5, 0));
    vertices.push_back(b2Vec2(5, 1));
    vertices.push_back(b2Vec2(4, 2));
    vertices.push_back(b2Vec2(1, 2));
    vertices.push_back(b2Vec2(0, 1));
    body = createPolygon(
        world, x, y, vertices, 100.f, 0.7f,
        sf::Color((int)(carColor[0] * 255), (int)(carColor[1] * 255), (int)(carColor[2] * 255)));

    // Create a circle
    frontWheel = createCircle(world, 350, 300, 20, 100.f, 0.7f, sf::Color(50, 200, 50));

    // Create another circle
    backWheel = createCircle(world, 350, 300, 20, 100.f, 0.7f, sf::Color(50, 200, 50));

    b2DistanceJointDef jointDef2;
    jointDef2.bodyA = body.body;
    jointDef2.bodyB = frontWheel.body;
    jointDef2.localAnchorA = b2Vec2(1.0, -1.0);
    jointDef2.localAnchorB = b2Vec2(0.0, 0.0);
    jointDef2.maxLength = 0.01;
    jointDef2.collideConnected = false;
    world->CreateJoint(&jointDef2);

    jointDef2.bodyA = body.body;
    jointDef2.bodyB = backWheel.body;
    jointDef2.localAnchorA = b2Vec2(4.0, -1.0);
    jointDef2.localAnchorB = b2Vec2(0.0, 0.0);
    jointDef2.maxLength = 0.01;
    jointDef2.collideConnected = false;
    world->CreateJoint(&jointDef2);
}

Polygon* Car::getBody() { return &body; }

Circle* Car::getFrontWheel() { return &frontWheel; }

Circle* Car::getBackWheel() { return &backWheel; }

sf::Color* Car::getBodyColor() { return &bodyColor; }
