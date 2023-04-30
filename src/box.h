#ifndef BOX_H
#define BOX_H

#include "../config/config.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

// A structure with all we need to render a box
struct Box {
    float width;
    float height;
    sf::Color color;
    b2Body* body;
};

Box createBox(b2World* world, float x, float y, float width, float height, float density,
              float friction, sf::Color color);

Box createGround(b2World* world, float x, float y, float width, float height, sf::Color color);

#endif
