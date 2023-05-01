#ifndef CONFIG_H
#define CONFIG_H

/*
Author: Mateusz Krakowski
Description: This file contains all the constant values used in the program.
*/

class Config {
   public:
    static constexpr int WINDOW_WIDTH = 1600;
    static constexpr int WINDOW_HEIGHT = 900;

    // Pixels per meter. Box2D uses metric units, so we need PPM for conversion pourposes
    static constexpr float PPM = 30.0F;

    // SFML uses degrees for angles while Box2D uses radians
    static constexpr float DEG_PER_RAD = 57.2957795F;
    static constexpr double GRAVITIATIONAL_ACCELERATION = -9.81f;
};

#endif  // CONFIG_H
