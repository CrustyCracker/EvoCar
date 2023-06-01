#include "Utility.h"

/*
Author:         Jakub Marcowski
Description:    -
*/

void applyAirResistance(Car car) {
    car.getBody()->body->ApplyForceToCenter(
        b2Vec2(-1.84 * car.getBody()->body->GetLinearVelocity().x *
                   abs(car.getBody()->body->GetLinearVelocity().x),
               -1.84 * car.getBody()->body->GetLinearVelocity().y *
                   abs(car.getBody()->body->GetLinearVelocity().y)),
        true);
}

void generateGround(b2WorldPtr world, std::vector<Box> *boxes, std::vector<Car> cars) {
    Box lastGround = boxes->back();
    const float generateDistance = 200;
    // if car is far enough to the right, generate a new ground
    if (lastGround.body->GetPosition().x * Config::PPM + lastGround.width / 2 <
        cars[0].getBody()->body->GetPosition().x * Config::PPM + generateDistance) {
        Box ground =
            createGround(world, lastGround.body->GetPosition().x * Config::PPM + lastGround.width,
                         50, 500, 100, sf::Color(50, 50, 50));
        boxes->push_back(ground);
    }
}
