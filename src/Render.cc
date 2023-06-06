/**
 * @brief This file contains the render function, which
 * is responsible for rendering all the shapes in the world.
 *
 * @file Render.cc
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#include "Render.h"

void renderCircle(sf::RenderWindow &w, Circle *circle) {
    sf::CircleShape circ;

    circ.setPosition(circle->body->GetPosition().x * Config::PPM,
                     Config::WINDOW_HEIGHT - (circle->body->GetPosition().y * Config::PPM));

    circ.setOrigin(circle->radius, circle->radius);

    circ.setRadius(circle->radius);

    circ.setRotation(-1 * circle->body->GetAngle() * Config::DEG_PER_RAD);

    circ.setFillColor(circle->color);
    w.draw(circ);
}

void renderCircleDebug(sf::RenderWindow &w, Circle *circle) {
    // Draw a line from the circle's center to its edge
    // (account for rotation if the body has non-zero torque)
    sf::Vertex line[] = {
        sf::Vertex(
            sf::Vector2f(circle->body->GetPosition().x * Config::PPM,
                         Config::WINDOW_HEIGHT - (circle->body->GetPosition().y * Config::PPM))),
        sf::Vertex(sf::Vector2f(
            circle->body->GetPosition().x * Config::PPM +
                circle->radius * cos(circle->body->GetAngle()),
            Config::WINDOW_HEIGHT - (circle->body->GetPosition().y * Config::PPM +
                                     circle->radius * sin(circle->body->GetAngle()))))};
    w.draw(line, 2, sf::Lines);
}

void renderPolygon(sf::RenderWindow &w, Polygon *polygon) {
    sf::ConvexShape convex;

    convex.setPosition(polygon->body->GetPosition().x * Config::PPM,
                       Config::WINDOW_HEIGHT - (polygon->body->GetPosition().y * Config::PPM));

    convex.setOrigin(0, 0);

    convex.setPointCount(polygon->vertices.size());
    for (int i = 0; i < polygon->vertices.size(); ++i) {
        convex.setPoint(i, sf::Vector2f(polygon->vertices[i].x * Config::PPM,
                                        polygon->vertices[i].y * Config::PPM));
    }

    convex.setRotation(-1 * polygon->body->GetAngle() * Config::DEG_PER_RAD);

    // Flip the polygon along the X axis
    convex.scale(1, -1);

    convex.setFillColor(polygon->color);
    w.draw(convex);
}

void renderPolygonDebug(sf::RenderWindow &w, Polygon *polygon) {
    // Draw the polygon's center
    sf::CircleShape circ;
    circ.setRadius(5);
    circ.setOrigin(5, 5);
    circ.setPosition(polygon->body->GetPosition().x * Config::PPM,
                     Config::WINDOW_HEIGHT - (polygon->body->GetPosition().y * Config::PPM));
    circ.setFillColor(sf::Color::Blue);
    w.draw(circ);

    // Draw the polygon's vertices
    for (int i = 0; i < polygon->vertices.size(); ++i) {
        circ.setRadius(2);
        circ.setOrigin(2, 2);
        circ.setPosition(polygon->body->GetWorldPoint(polygon->vertices[i]).x * Config::PPM,
                         Config::WINDOW_HEIGHT -
                             (polygon->body->GetWorldPoint(polygon->vertices[i]).y * Config::PPM));
        circ.setFillColor(sf::Color::White);
        w.draw(circ);
    }
}

void renderCar(sf::RenderWindow &w, Car car) {
    renderPolygon(w, car.getBody());
    renderCircle(w, car.getFrontWheel());
    renderCircle(w, car.getBackWheel());
    if (Config::DEBUG) {
        renderPolygonDebug(w, car.getBody());
        renderCircleDebug(w, car.getFrontWheel());
        renderCircleDebug(w, car.getBackWheel());
    }
}

void render(sf::RenderWindow &w, const std::vector<sf::Sprite> &BGs,
            std::vector<Polygon> &groundVector, std::vector<Car> &cars) {
    w.clear();
    for (const sf::Sprite &BG : BGs) {
        w.draw(BG);
    }

    int groundBeginIndex = 0;
    int centerIndex = getIndexOfGroundClosestToLocation(groundVector, getFurthestCarPos(cars).x);
    int groundEndIndex = groundVector.size();

    if (centerIndex - Config::GROUND_PARTS_RENDERED / 2 > 0) {
        groundBeginIndex = centerIndex - Config::GROUND_PARTS_RENDERED / 2;
    }
    if (centerIndex + Config::GROUND_PARTS_RENDERED / 2 < groundEndIndex) {
        groundEndIndex = centerIndex + Config::GROUND_PARTS_RENDERED / 2;
    }
    std::vector<Polygon> groundSlice(groundVector.begin() + groundBeginIndex,
                                     groundVector.begin() + groundEndIndex);

    for (Polygon ground : groundSlice) {
        renderPolygon(w, &ground);
        if (Config::DEBUG) {
            renderPolygonDebug(w, &ground);
        }
    }

    // new cars should be rendered behind the old ones
    for (int i = cars.size() - 1; i >= 0; --i) {
        renderCar(w, cars[i]);
    }
}
