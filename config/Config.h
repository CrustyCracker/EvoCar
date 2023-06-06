/**
 * @brief This file contains all the constant values used in the program.
 *
 * @file Config.h
 * @authors Jakub Marcowski, Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef CONFIG_H
#define CONFIG_H

class Config {
   public:
    static constexpr int WINDOW_WIDTH = 1280;
    static constexpr int WINDOW_HEIGHT = 720;

    // 60 for real time, 120 for fast forward - anything else is undefined behaviour
    static constexpr int MAX_FPS = 60;
    static constexpr int GROUND_PARTS_RENDERED = 32;

    static constexpr bool SAVE_TO_FILE = false;

    static constexpr int GENERATION_TIME =
        3000;  // in frames, about 60 frames per second => 50 seconds
    // Pixels per meter. Box2D uses metric units, so we need PPM for conversion purposes
    static constexpr float PPM = 30.0F;

    // SFML uses degrees for angles while Box2D uses radians
    static constexpr float DEG_PER_RAD = 57.2957795F;
    static constexpr int COLOR_CONST = 255;

    // Draw debug geometry
    static constexpr bool DEBUG = true;

    // Physics
    static constexpr double GRAVITATIONAL_ACCELERATION = -9.81f;
    static constexpr float FRICTION = 0.3f;
    static constexpr int VELOCITY_ARRAY_SIZE = 1000;

    static constexpr double PI = 3.14159265358979323846;
    static constexpr int BACK_WHEEL_POS = 1;
    static constexpr int FRONT_WHEEL_POS = 3;
    static constexpr int CATEGORY_BITS = 2;
    static constexpr int MASK_BITS = 1;
};

#endif  // CONFIG_H
