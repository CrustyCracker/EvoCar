#ifndef CONFIG_H
#define CONFIG_H

/*
Author: Mateusz Krakowski, Jakub Marcowski
Description: This file contains all the constant values used in the program.
*/

class Config {
   public:
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;

    // Pixels per meter. Box2D uses metric units, so we need PPM for conversion pourposes
    static constexpr float PPM = 30.0F;

    // SFML uses degrees for angles while Box2D uses radians
    static constexpr float DEG_PER_RAD = 57.2957795F;
    static constexpr int COLOR_CONST = 255;

    // Draw debug geometry
    static constexpr bool DEBUG = true;

    // Psychics
    static constexpr double GRAVITIATIONAL_ACCELERATION = -9.81f;
    static constexpr float FRICTION = 0.3f;
    static constexpr double PI = 3.14159265358979323846;
};

#endif  // CONFIG_H
