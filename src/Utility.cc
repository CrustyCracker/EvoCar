/**
 * @brief File containing utility functions.
 *
 * @file Utility.cc
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#include "Utility.h"

void applyAirResistance(Car car) {
    // F = V^2 * k
    // k ≈ 1/2 * ρ * A * C_d ≈ 3.4
    // ρ = 1.293 kg/m^3
    // A = ? (let's assume 5 m^2)
    // C_d = ? (let's assume 1.05)
    //
    // F = 3.4 * V^2
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

        std::vector<b2Vec2> groundVertices = {
            b2Vec2(lastGround.vertices[1].x, lastGround.vertices[1].y),
            b2Vec2(lastGround.vertices[1].x + delta_x, lastGround.vertices[1].y + delta_y),
            b2Vec2(lastGround.vertices[2].x + delta_x, lastGround.vertices[2].y + delta_y)};

        Polygon ground =
            createGround(world, MapGenConfig::GROUND_STARTING_X, MapGenConfig::GROUND_STARTING_Y,
                         groundVertices, sf::Color(18, 36, 35));

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

int getIndexOfGroundClosestToLocation(std::vector<Polygon> ground, float x) {
    int index = 0;
    for (int i = 0; i < ground.size(); ++i) {
        if (ground[i].vertices[0].x - x > 0) {
            break;
        }
        index = i;
    }
    return index;
}

void removeCars(b2WorldPtr world, std::vector<Car>* cars) {
    for (auto car : *cars) {
        world->DestroyBody(car.getBody()->body);
        world->DestroyBody(car.getBackWheel()->body);
        world->DestroyBody(car.getFrontWheel()->body);
    }
    cars->clear();
}

std::filesystem::path getRootDir() {
    std::filesystem::path filePath = std::filesystem::path(__FILE__);
    std::filesystem::path dirPath = filePath.parent_path();
    return dirPath;
}

void setIcon(sf::RenderWindow& window) {
    std::string iconPath = (getRootDir() / "../resources/evoracer_icon.png").string();
    auto icon = sf::Image{};
    if (icon.loadFromFile(iconPath)) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
}

std::vector<sf::Texture*> loadBGTextures() {
    std::vector<sf::Texture*> textures;
    for (int i = 0; i < MapGenConfig::BG_SPRITES_COUNT; ++i) {
        std::string BGPath =
            (getRootDir() / ("../resources/background_img_" + std::to_string(i) + ".png")).string();
        sf::Texture* texture = new sf::Texture();
        texture->loadFromFile(BGPath);
        texture->setRepeated(true);
        textures.push_back(texture);
    }
    return textures;
}

sf::Sprite loadBGSprite(sf::Texture* texture, std::vector<Car> cars) {
    sf::Sprite sprite(*texture);
    sprite.setScale(sf::Vector2f(Config::WINDOW_WIDTH / sprite.getLocalBounds().width,
                                 Config::WINDOW_HEIGHT / sprite.getLocalBounds().height));
    sprite.setTextureRect(sf::IntRect(0, 0, 256 * Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
    sprite.setPosition(
        sf::Vector2f(getFurthestCarX(cars) * Config::PPM, 0.5 * Config::WINDOW_HEIGHT) -
        sf::Vector2f(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2));
    return sprite;
}

std::vector<sf::Sprite> loadBGSprites(std::vector<sf::Texture*> textures, std::vector<Car> cars) {
    std::vector<sf::Sprite> sprites;
    for (int i = 0; i < MapGenConfig::BG_SPRITES_COUNT; ++i) {
        sprites.push_back(loadBGSprite(textures[i], cars));
    }
    return sprites;
}
