/**
 * @brief Creates a car with a polygon (car's body)
 * and two circles (front and back wheels).
 *
 * @file Car.cc
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#include "Car.h"

Car::Car(const b2WorldPtr& world, float x, float y, const Chromosome& chromosome,
         sf::Color bodyColor, sf::Color wheelColor) {
    // Create a polygon (octagon)

    auto vertices = createVertices(chromosome.bodyLengths);

    body_ =
        createPolygon(world, x, y, vertices, chromosome.bodyDensity, Config::FRICTION, bodyColor);

    // Create a circle
    frontWheel_ = createCircle(world, x, y, chromosome.wheelRadius.first,
                               chromosome.wheelDensity.first, Config::FRICTION, wheelColor);

    // Create another circle
    backWheel_ = createCircle(world, x, y, chromosome.wheelRadius.second,
                              chromosome.wheelDensity.second, Config::FRICTION, wheelColor);

    b2DistanceJointDef jointDef2;
    jointDef2.bodyA = body_.body;
    jointDef2.bodyB = frontWheel_.body;
    jointDef2.localAnchorA = vertices[Config::BACK_WHEEL_POS];
    jointDef2.localAnchorB = b2Vec2(0.0f, 0.0f);
    jointDef2.maxLength = CarConfig::MAX_JOINT_LENGTH;
    jointDef2.collideConnected = false;
    world->CreateJoint(&jointDef2);

    jointDef2.bodyA = body_.body;
    jointDef2.bodyB = backWheel_.body;
    jointDef2.localAnchorA = vertices[Config::FRONT_WHEEL_POS];
    jointDef2.localAnchorB = b2Vec2(0.0f, 0.0f);
    jointDef2.maxLength = CarConfig::MAX_JOINT_LENGTH;
    jointDef2.collideConnected = false;
    world->CreateJoint(&jointDef2);

    // Make cars pass through each-other
    // by setting collision filtering
    b2Filter filter;
    filter.categoryBits = Config::CATEGORY_BITS;
    filter.maskBits = Config::MASK_BITS;
    this->setCollisionFilter(filter);

    std::vector<float> v_axis(Config::VELOCITY_ARRAY_SIZE);
    std::vector<float> v_values(Config::VELOCITY_ARRAY_SIZE);

    std::iota(std::begin(v_axis), std::end(v_axis), 1);

    velX_ = v_axis;
    velY_ = v_values;
}

Polygon* Car::getBody() { return &body_; }

Circle* Car::getFrontWheel() { return &frontWheel_; }

Circle* Car::getBackWheel() { return &backWheel_; }

float Car::getPosX() const { return body_.body->GetPosition().x; }

float Car::getPosY() const { return body_.body->GetPosition().y; }

std::vector<float>* Car::getVelX() { return &velX_; }

std::vector<float>* Car::getVelY() { return &velY_; }

sf::Color Car::getBodyColor() const { return body_.color; }

b2Vec2 Car::getVelocityVec() const { return body_.body->GetLinearVelocity(); }

float Car::getVelocity() const { return body_.body->GetLinearVelocity().Length(); }

void Car::setCollisionFilter(b2Filter filter) const {
    body_.body->GetFixtureList()->SetFilterData(filter);
    frontWheel_.body->GetFixtureList()->SetFilterData(filter);
    backWheel_.body->GetFixtureList()->SetFilterData(filter);
}

std::vector<b2Vec2> createVertices(std::vector<float> lengths) {
    std::vector<b2Vec2> vertices;

    std::vector<float> angles;
    angles.reserve(lengths.size());
    for (int i = 0; i < lengths.size(); i++) {
        angles.push_back(360.0f / lengths.size());
    }
    // so that the wheels are set properly (that is - parallel to the ground)
    float angle = ((180.0f + (angles.back() / 2)) / 180.0f) * Config::PI;

    for (int i = 0; i < lengths.size(); i++) {
        vertices.emplace_back(lengths[i] * cos(angle), lengths[i] * sin(angle));
        angle += (angles[i] / 180.0f) * Config::PI;
    }
    return vertices;
}
