#include "Utility.h"

/*
Author:         Jakub Marcowski
Description:    File containing utility functions.
*/

void applyAirResistance(Car car) {
    car.getBody()->body->ApplyForceToCenter(
        b2Vec2(-1.84 * car.getBody()->body->GetLinearVelocity().x *
                   abs(car.getBody()->body->GetLinearVelocity().x),
               -1.84 * car.getBody()->body->GetLinearVelocity().y *
                   abs(car.getBody()->body->GetLinearVelocity().y)),
        true);
}

void generateGround(b2WorldPtr world, std::vector<Box>* boxes, std::vector<Car> cars) {
    Box lastGround = boxes->back();
    const float generateDistance = 700;
    // if car is far enough to the right, generate a new ground
    if (lastGround.body->GetPosition().x * Config::PPM + lastGround.width / 2 <
        cars[0].getBody()->body->GetPosition().x * Config::PPM + generateDistance) {
        Box ground =
            createGround(world, lastGround.body->GetPosition().x * Config::PPM + lastGround.width,
                         50, 500, 100, sf::Color(50, 50, 50));
        boxes->push_back(ground);
    }
}

Car generateRandomCar(b2WorldPtr world) {
    auto vertices_gen = createVertices(
        {2.54951f, 2.12132f, 2.12132f, 2.54951f, 2.54951f, 2.12132f, 2.12132f, 2.54951f},
        {33.7f, 90.0f, 33.7f, 22.6f, 33.7f, 90.0f, 33.7f, 22.6f});

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rgb_value(50, 200);

    sf::Color bodyColor = sf::Color(rgb_value(gen), rgb_value(gen), rgb_value(gen));
    sf::Color wheelColor = sf::Color(rgb_value(gen), rgb_value(gen), rgb_value(gen));

    return Car(world, 250, 300, vertices_gen, 100.0f, 25.0f, bodyColor, wheelColor);
}

ImVec4 SFMLColorToImVec4(sf::Color color) {
    return ImVec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}
