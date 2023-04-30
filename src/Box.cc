#include "Box.h"
/*
Author:
Description:
*/

Box createBox(b2World* world, float x, float y, float width, float height, float density,
              float friction, sf::Color color) {
    // Body definition
    b2BodyDef boxBodyDef;
    boxBodyDef.position.Set(x / Config::PPM, y / Config::PPM);
    boxBodyDef.type = b2_dynamicBody;

    // Shape definition
    b2PolygonShape boxShape;
    boxShape.SetAsBox(width / 2 / Config::PPM, height / 2 / Config::PPM);

    // Fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.shape = &boxShape;

    // Now we have a body for our Box object
    b2Body* boxBody = world->CreateBody(&boxBodyDef);
    // Lastly, assign the fixture
    boxBody->CreateFixture(&fixtureDef);

    return Box{width, height, color, boxBody};
}

Box createGround(b2World* world, float x, float y, float width, float height, sf::Color color) {
    // Static body definition
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x / Config::PPM, y / Config::PPM);

    // Shape definition
    b2PolygonShape groundBox;
    groundBox.SetAsBox(width / 2 / Config::PPM, height / 2 / Config::PPM);

    // Now we have a body for our Box object
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    // For a static body, we don't need a custom fixture definition, this will do:
    groundBody->CreateFixture(&groundBox, 0.0f);

    return Box{width, height, color, groundBody};
}
