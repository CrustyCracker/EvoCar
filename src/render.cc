#include "render.h"

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
