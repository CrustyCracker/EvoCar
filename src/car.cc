#include "car.h"

Polygon createCar(b2World* world, std::vector<Polygon>* polygons, std::vector<Circle>* circles,
                  float carColor[3]) {
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
    auto&& polygon = createPolygon(
        world, 350, 300, vertices, 100.f, 0.7f,
        sf::Color((int)(carColor[0] * 255), (int)(carColor[1] * 255), (int)(carColor[2] * 255)));
    polygons->push_back(polygon);

    // Create a circle
    auto&& circle1 = createCircle(world, 350, 300, 20, 100.f, 0.7f, sf::Color(50, 200, 50));
    circles->push_back(circle1);

    // Create another circle
    auto&& circle2 = createCircle(world, 350, 300, 20, 100.f, 0.7f, sf::Color(50, 200, 50));
    circles->push_back(circle2);

    b2DistanceJointDef jointDef2;
    jointDef2.bodyA = polygon.body;
    jointDef2.bodyB = circle1.body;
    jointDef2.localAnchorA = b2Vec2(1.0, -1.0);
    jointDef2.localAnchorB = b2Vec2(0.0, 0.0);
    jointDef2.maxLength = 0.01;
    jointDef2.collideConnected = false;
    world->CreateJoint(&jointDef2);

    jointDef2.bodyA = polygon.body;
    jointDef2.bodyB = circle2.body;
    jointDef2.localAnchorA = b2Vec2(4.0, -1.0);
    jointDef2.localAnchorB = b2Vec2(0.0, 0.0);
    jointDef2.maxLength = 0.01;
    jointDef2.collideConnected = false;
    world->CreateJoint(&jointDef2);

    return polygon;
}
