#include "Car.h"

/*
Author:         Jakub Marcowski, Mateusz Krakowski
Description:    Creates a car with a polygon (car's body)
    and two circles (front and back wheels).
*/

Car::Car(b2WorldPtr world, float x, float y, Chromosome chromosome, sf::Color bodyColor,
         sf::Color wheelColor) {
    // Create a polygon (octagon)

    auto vertices =
        createVertices(chromosome.bodyLengths, {45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0, 45.0});

    body =
        createPolygon(world, x, y, vertices, chromosome.bodyDensity, Config::FRICTION, bodyColor);

    // Create a circle
    frontWheel = createCircle(world, x, y, chromosome.wheelRadius.first,
                              chromosome.wheelDensity.first, Config::FRICTION, wheelColor);

    // Create another circle
    backWheel = createCircle(world, x, y, chromosome.wheelRadius.second,
                             chromosome.wheelDensity.second, Config::FRICTION, wheelColor);

    b2DistanceJointDef jointDef2;
    jointDef2.bodyA = body.body;
    jointDef2.bodyB = frontWheel.body;
    jointDef2.localAnchorA = vertices[1];
    jointDef2.localAnchorB = b2Vec2(0.0f, 0.0f);
    jointDef2.maxLength = CarConfig::MAX_JOINT_LENGTH;
    jointDef2.collideConnected = false;
    world->CreateJoint(&jointDef2);

    jointDef2.bodyA = body.body;
    jointDef2.bodyB = backWheel.body;
    jointDef2.localAnchorA = vertices[2];
    jointDef2.localAnchorB = b2Vec2(0.0f, 0.0f);
    jointDef2.maxLength = CarConfig::MAX_JOINT_LENGTH;
    jointDef2.collideConnected = false;
    world->CreateJoint(&jointDef2);

    // Make cars pass through eachother
    // by setting collision filtering
    b2Filter filter;
    filter.categoryBits = 2;
    filter.maskBits = 1;
    this->setCollisionFilter(filter);

    std::vector<float> v_axis(Config::VELOCITY_ARRAY_SIZE);
    std::vector<float> v_values(Config::VELOCITY_ARRAY_SIZE);

    std::iota(std::begin(v_axis), std::end(v_axis), 1);

    velX = v_axis;
    velY = v_values;
}

Polygon* Car::getBody() { return &body; }

Circle* Car::getFrontWheel() { return &frontWheel; }

Circle* Car::getBackWheel() { return &backWheel; }

float Car::getPosX() { return body.body->GetPosition().x; }

float Car::getPosY() { return body.body->GetPosition().y; }

std::vector<float>* Car::getVelX() { return &velX; }

std::vector<float>* Car::getVelY() { return &velY; }

sf::Color Car::getBodyColor() { return body.color; }

b2Vec2 Car::getVelocityVec() { return body.body->GetLinearVelocity(); }

float Car::getVelocity() { return body.body->GetLinearVelocity().Length(); }

void Car::setCollisionFilter(b2Filter filter) {
    body.body->GetFixtureList()->SetFilterData(filter);
    frontWheel.body->GetFixtureList()->SetFilterData(filter);
    backWheel.body->GetFixtureList()->SetFilterData(filter);
}

std::vector<b2Vec2> createVertices(std::vector<float> lengths, std::vector<float> angles) {
    std::vector<b2Vec2> vertices;

    // so that the wheels are set properly (that is - parallel to the ground)
    float angle = ((180.0f + (angles.back() / 2)) / 180.0f) * Config::PI;

    for (int i = 0; i < lengths.size(); i++) {
        vertices.push_back(b2Vec2(lengths[i] * cos(angle), lengths[i] * sin(angle)));
        angle += (angles[i] / 180.0f) * Config::PI;
    }
    return vertices;
}
