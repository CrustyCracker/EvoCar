#include <iostream>

#include "../config/config.h"
#include "../include/SFML/Graphics.hpp"
#include "../include/box2d/box2d.h"
#include "../include/imgui/imgui-SFML.h"
#include "../include/imgui/imgui.h"

b2World world(b2Vec2(0, -9.81));
// A structure with all we need to render a box
struct Box {
    float width;
    float height;
    sf::Color color;
    b2Body *body;
};

struct Polygon {
    std::vector<b2Vec2> vertices;
    sf::Color color;
    b2Body *body;
};

struct Circle {
    float radius;
    sf::Color color;
    b2Body *body;
};

Box createBox(float x, float y, float width, float height, float density, float friction,
              sf::Color color) {
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
    b2Body *boxBody = world.CreateBody(&boxBodyDef);
    // Lastly, assign the fixture
    boxBody->CreateFixture(&fixtureDef);

    return Box{width, height, color, boxBody};
}

Polygon createPolygon(float x, float y, std::vector<b2Vec2> vertices, float density, float friction,
                      sf::Color color) {
    // Body definition
    b2BodyDef boxBodyDef;
    boxBodyDef.position.Set(x / Config::PPM, y / Config::PPM);
    boxBodyDef.type = b2_dynamicBody;

    // Shape definition
    b2PolygonShape boxShape;
    boxShape.Set(vertices.data(), vertices.size());

    // Fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.shape = &boxShape;

    // Now we have a body for our Box object
    b2Body *boxBody = world.CreateBody(&boxBodyDef);
    // Lastly, assign the fixture
    boxBody->CreateFixture(&fixtureDef);

    return Polygon{vertices, color, boxBody};
}

Circle createCircle(float x, float y, float radius, float density, float friction,
                    sf::Color color) {
    // Body definition
    b2BodyDef boxBodyDef;
    boxBodyDef.position.Set(x / Config::PPM, y / Config::PPM);
    boxBodyDef.type = b2_dynamicBody;

    // Shape definition
    b2CircleShape circleShape;
    circleShape.m_radius = radius / Config::PPM;

    // Fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.shape = &circleShape;

    // Now we have a body for our Box object
    b2Body *boxBody = world.CreateBody(&boxBodyDef);
    // Lastly, assign the fixture
    boxBody->CreateFixture(&fixtureDef);

    return Circle{radius, color, boxBody};
}

Box createGround(float x, float y, float width, float height, sf::Color color) {
    // Static body definition
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x / Config::PPM, y / Config::PPM);

    // Shape definition
    b2PolygonShape groundBox;
    groundBox.SetAsBox(width / 2 / Config::PPM, height / 2 / Config::PPM);

    // Now we have a body for our Box object
    b2Body *groundBody = world.CreateBody(&groundBodyDef);
    // For a static body, we don't need a custom fixture definition, this will do:
    groundBody->CreateFixture(&groundBox, 0.0f);

    return Box{width, height, color, groundBody};
}

void render(sf::RenderWindow &w, std::vector<Box> &boxes, std::vector<Polygon> &polygons,
            std::vector<Circle> &circles) {
    w.clear();
    for (const auto &box : boxes) {
        sf::RectangleShape rect;

        // For the correct Y coordinate of our drawable rect, we must substract from
        // Config::WINDOW_HEIGHT because SFML uses OpenGL coordinate system where X is
        // right, Y is down while Box2D uses traditional X is right, Y is up
        rect.setPosition(box.body->GetPosition().x * Config::PPM,
                         Config::WINDOW_HEIGHT - (box.body->GetPosition().y * Config::PPM));

        // We also need to set our drawable's origin to its center
        // because in SFML, "position" refers to the upper left corner
        // while in Box2D, "position" refers to the body's center
        rect.setOrigin(box.width / 2, box.height / 2);

        rect.setSize(sf::Vector2f(box.width, box.height));

        // For the rect to be rotated in the correct direction, we have to multiply by -1
        rect.setRotation(-1 * box.body->GetAngle() * Config::DEG_PER_RAD);

        rect.setFillColor(box.color);
        w.draw(rect);
    }
    for (const auto &polygon : polygons) {
        sf::ConvexShape convex;

        // For the correct Y coordinate of our drawable rect, we must substract from
        // Config::WINDOW_HEIGHT because SFML uses OpenGL coordinate system where X is
        // right, Y is down while Box2D uses traditional X is right, Y is up
        convex.setPosition(polygon.body->GetPosition().x * Config::PPM,
                           Config::WINDOW_HEIGHT - (polygon.body->GetPosition().y * Config::PPM));

        // We also need to set our drawable's origin to its center
        // because in SFML, "position" refers to the upper left corner
        // while in Box2D, "position" refers to the body's center
        convex.setOrigin(0, 0);

        convex.setPointCount(polygon.vertices.size());
        for (int i = 0; i < polygon.vertices.size(); i++) {
            convex.setPoint(i, sf::Vector2f(polygon.vertices[i].x * Config::PPM,
                                            polygon.vertices[i].y * Config::PPM));
        }

        // For the rect to be rotated in the correct direction, we have to multiply by -1
        convex.setRotation(-1 * polygon.body->GetAngle() * Config::DEG_PER_RAD);

        // Flip the polygon along the X axis
        convex.scale(1, -1);

        convex.setFillColor(polygon.color);
        w.draw(convex);
    }
    for (const auto &circle : circles) {
        sf::CircleShape circ;

        // For the correct Y coordinate of our drawable rect, we must substract from
        // Config::WINDOW_HEIGHT because SFML uses OpenGL coordinate system where X is
        // right, Y is down while Box2D uses traditional X is right, Y is up
        circ.setPosition(circle.body->GetPosition().x * Config::PPM,
                         Config::WINDOW_HEIGHT - (circle.body->GetPosition().y * Config::PPM));

        // We also need to set our drawable's origin to its center
        // because in SFML, "position" refers to the upper left corner
        // while in Box2D, "position" refers to the body's center
        circ.setOrigin(circle.radius, circle.radius);

        circ.setRadius(circle.radius);

        // For the rect to be rotated in the correct direction, we have to multiply by -1
        circ.setRotation(-1 * circle.body->GetAngle() * Config::DEG_PER_RAD);

        circ.setFillColor(circle.color);
        w.draw(circ);

        // Draw a line from the circle's center to its edge
        // (account for rotation if the body has non-zero torque)
        sf::Vertex line[] = {
            sf::Vertex(
                sf::Vector2f(circle.body->GetPosition().x * Config::PPM,
                             Config::WINDOW_HEIGHT - (circle.body->GetPosition().y * Config::PPM))),
            sf::Vertex(sf::Vector2f(
                circle.body->GetPosition().x * Config::PPM +
                    circle.radius * cos(circle.body->GetAngle()),
                Config::WINDOW_HEIGHT - (circle.body->GetPosition().y * Config::PPM +
                                         circle.radius * sin(circle.body->GetAngle()))))};
        w.draw(line, 2, sf::Lines);
    }
    for (const auto &polygon : polygons) {
        // Draw the polygon's center
        sf::CircleShape circ;
        circ.setRadius(5);
        circ.setOrigin(5, 5);
        circ.setPosition(polygon.body->GetPosition().x * Config::PPM,
                         Config::WINDOW_HEIGHT - (polygon.body->GetPosition().y * Config::PPM));
        circ.setFillColor(sf::Color::Blue);
        w.draw(circ);

        // Draw the polygon's vertices
        for (int i = 0; i < polygon.vertices.size(); i++) {
            sf::CircleShape circ;
            circ.setRadius(2);
            circ.setOrigin(2, 2);
            circ.setPosition(
                polygon.body->GetWorldPoint(polygon.vertices[i]).x * Config::PPM,
                Config::WINDOW_HEIGHT -
                    (polygon.body->GetWorldPoint(polygon.vertices[i]).y * Config::PPM));
            circ.setFillColor(sf::Color::White);
            w.draw(circ);
        }
    }
}

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Setup SFML window
    sf::RenderWindow w(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "SFML + Box2D",
                       sf::Style::Default, settings);
    w.setFramerateLimit(60);

    // Initialize ImGui-SFML
    if (!ImGui::SFML::Init(w)) {
        return -1;
    }

    // Change imgui.ini location
    ImGui::GetIO().IniFilename = "build/imgui.ini";

    // Container to hold all the boxes we create
    std::vector<Box> boxes;

    // Container to hold all the polygons we create
    std::vector<Polygon> polygons;

    // Container to hold all the circles we create
    std::vector<Circle> circles;

    // Generate ground
    boxes.push_back(createGround(350, 50, 500, 100, sf::Color(50, 50, 50)));

    // Add a wall (uses "ground" object, for now)
    boxes.push_back(createGround(50, 350, 100, 700, sf::Color(50, 50, 50)));

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
    float carColor[3] = {(float)200 / 255, (float)50 / 255, (float)50 / 255};
    auto &&polygon = createPolygon(
        350, 300, vertices, 100.f, 0.7f,
        sf::Color((int)(carColor[0] * 255), (int)(carColor[1] * 255), (int)(carColor[2] * 255)));
    polygons.push_back(polygon);

    // Create a circle
    auto &&circle1 = createCircle(350, 300, 20, 100.f, 0.7f, sf::Color(50, 200, 50));
    circles.push_back(circle1);

    // Create another circle
    auto &&circle2 = createCircle(350, 300, 20, 100.f, 0.7f, sf::Color(50, 200, 50));
    circles.push_back(circle2);

    b2DistanceJointDef jointDef2;
    jointDef2.bodyA = polygon.body;
    jointDef2.bodyB = circle1.body;
    jointDef2.localAnchorA = b2Vec2(1.0, -1.0);
    jointDef2.localAnchorB = b2Vec2(0.0, 0.0);
    jointDef2.maxLength = 0.01;
    jointDef2.collideConnected = false;
    world.CreateJoint(&jointDef2);

    jointDef2.bodyA = polygon.body;
    jointDef2.bodyB = circle2.body;
    jointDef2.localAnchorA = b2Vec2(4.0, -1.0);
    jointDef2.localAnchorB = b2Vec2(0.0, 0.0);
    jointDef2.maxLength = 0.01;
    jointDef2.collideConnected = false;
    world.CreateJoint(&jointDef2);

    sf::Clock deltaClock;
    /** GAME LOOP **/
    while (w.isOpen()) {
        // Update the world, standard arguments
        world.Step(1 / 60.f, 6, 3);
        // Render everything
        render(w, boxes, polygons, circles);

        ImGui::SFML::Update(w, deltaClock.restart());

        ImGui::SetNextWindowSize(ImVec2(420, 160), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::Begin("Car Demo");
        ImGui::Text("Left/Right arrow keys to rotate the wheels.");
        ImGui::Text("Hold C to attach the camera to the car.");
        ImGui::Text("");

        ImGui::BeginChild("Car Settings");
        ImGui::ColorEdit3("\"Body\" Color", carColor);
        polygons[0].color =
            sf::Color((int)(carColor[0] * 255), (int)(carColor[1] * 255), (int)(carColor[2] * 255));

        ImGui::SliderFloat("Wheel 1 Radius [px]", &circles[0].radius, 0.0f, 100.0f);
        circles[0].body->GetFixtureList()->GetShape()->m_radius = circles[0].radius / Config::PPM;

        ImGui::SliderFloat("Wheel 2 Radius [px]", &circles[1].radius, 0.0f, 100.0f);
        circles[1].body->GetFixtureList()->GetShape()->m_radius = circles[1].radius / Config::PPM;
        ImGui::EndChild();

        ImGui::End();

        ImGui::SFML::Render(w);

        w.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            // Attach camera to the polygon
            sf::View cameraView = sf::View(
                sf::Vector2f(polygon.body->GetPosition().x * Config::PPM,
                             Config::WINDOW_HEIGHT - (polygon.body->GetPosition().y * Config::PPM)),
                sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
            cameraView.setRotation((-1) * polygon.body->GetAngle() * 180 / b2_pi);
            w.setView(cameraView);
        } else {
            // Reset camera
            sf::View cameraView =
                sf::View(sf::Vector2f(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2),
                         sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
            w.setView(cameraView);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // Rotate the circles left
            for (const auto &circle : circles) {
                circle.body->ApplyTorque(1000, false);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            // Rotate the circles right
            for (const auto &circle : circles) {
                circle.body->ApplyTorque(-1000, false);
            }
        }

        // Display FPS in window title
        w.setTitle("SFML + Box2D, FPS: " + std::to_string((int)ImGui::GetIO().Framerate));

        // Process events
        sf::Event event;
        while (w.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                w.close();
            }
        }
    }
    ImGui::SFML::Shutdown();
    return 0;
}
