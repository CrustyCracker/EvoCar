#include "../config/config.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

struct Circle {
    float radius;
    sf::Color color;
    b2Body *body;
};

Circle createCircle(b2World* world, float x, float y, float radius, float density, float friction, sf::Color color);
