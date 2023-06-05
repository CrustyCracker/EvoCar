#include "Utility.h"

/*
Author:         Jakub Marcowski, Mateusz Krakowski
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

void generateGround(b2WorldPtr world, std::vector<Polygon>* groundVector, std::vector<Car> cars) {
    Polygon lastGround = groundVector->back();
    if (lastGround.vertices[1].x * Config::PPM <
        getFurthestCarX(cars) * Config::PPM + MapGenConfig::GENERATE_DISTANCE) {
        float degree = getNextGroundPartDegree();
        float angle_in_radians = degree * (M_PI / 180.0f);

        float delta_x = MapGenConfig::GROUND_PART_LENGTH * cos(angle_in_radians);
        float delta_y = -MapGenConfig::GROUND_PART_LENGTH * sin(angle_in_radians);

        std::vector<b2Vec2> groundVertecies = {
            b2Vec2(lastGround.vertices[1].x, lastGround.vertices[1].y),
            b2Vec2(lastGround.vertices[1].x + delta_x, lastGround.vertices[1].y + delta_y),
            b2Vec2(lastGround.vertices[2].x + delta_x, lastGround.vertices[2].y + delta_y)};

        Polygon ground =
            createGround(world, MapGenConfig::GROUND_STARTING_X, MapGenConfig::GROUND_STARTING_Y,
                         groundVertecies, sf::Color(18, 36, 35));

        groundVector->push_back(ground);
    }
}

float getNextGroundPartDegree() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(0.0, MapGenConfig::GROUND_DEGREE_DEVIATION);

    float degree = dist(gen);
    if (degree > MapGenConfig::MAX_GROUND_DEGREE) {
        degree = MapGenConfig::MAX_GROUND_DEGREE;
    } else if (degree < -MapGenConfig::MAX_GROUND_DEGREE) {
        degree = -MapGenConfig::MAX_GROUND_DEGREE;
    }

    return degree;
}

// Note: this doesn't remove ground boxes from
// the world, it only stops them from rendering
// off screen (iterating over thousands of ground
// parts, when only ~30 are visible, is a complete
// waste of resources)
void removeOldGroundParts(std::vector<Polygon>* boxes) {  // New idea:
    // TODO: change this condition to                        instead of calling
    // one that takes into account whether the               this function to trim
    // ground boxes are off the screen                       the vector, we could
    if (boxes->size() > 32) {          //                    iterate over a slice
        boxes->erase(boxes->begin());  //                    in the render function
    }
}

Car generateCar(b2WorldPtr world, Chromosome chromosome) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rgb_value(50, 200);

    sf::Color bodyColor = sf::Color(rgb_value(gen), rgb_value(gen), rgb_value(gen));
    sf::Color wheelColor = sf::Color(rgb_value(gen), rgb_value(gen), rgb_value(gen));

    return Car(world, MapGenConfig::CAR_STARTING_X, MapGenConfig::CAR_STARTING_Y, chromosome,
               bodyColor, wheelColor);
}
ImVec4 SFMLColorToImVec4(sf::Color color) {
    return ImVec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}

float getFurthestCarX(std::vector<Car> cars) {
    float furthestCarX = 0;
    for (auto car : cars) {
        float currentCarX = car.getBody()->body->GetPosition().x;
        if (currentCarX > furthestCarX) {
            furthestCarX = currentCarX;
        }
    }
    return furthestCarX;
}

std::string replaceSubstring(std::string str, const std::string& from, const std::string& to) {
    size_t index = 0;
    while (true) {
        index = str.find(from, index);
        if (index == std::string::npos) {
            break;
        }
        str.replace(index, from.length(), to);
        index += to.length();
    }
    return str;
}
