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
    static constexpr double GRAVITIATIONAL_ACCELERATION = -9.81f;
    static constexpr int COLOR_CONST = 255;
    static constexpr float MAX_JOINT_LENGTH = 0.01f;

    // Number of vertices in a car's body polygon
    static constexpr int CAR_VERTICES = 8;

    // Draw debug geometry
    static constexpr bool DEBUG = true;


    // Evolutionary algorithm parameters
    static constexpr int POPULATION_SIZE = 10;
    // const float mutationRateBodyLengths = 0.1;
    // const float mutationRateBodyDensity = 0.05;
    // const float mutationRateWheelRadius = 0.2;
    // const float mutationRateWheelDensity = 0.1;
    static constexpr float MIN_BODY_LENGTH = 1.0f;
    static constexpr float MAX_BODY_LENGTH = 10.0f;
    
    static constexpr float MIN_BODY_DENSITY = 0.1f;
    static constexpr float MAX_BODY_DENSITY = 10.0f;

    static constexpr float MIN_WHEEL_RADIUS = 0.1f;
    static constexpr float MAX_WHEEL_RADIUS = 1.0f;

    static constexpr float MIN_WHEEL_DENSITY = 0.1f;
    static constexpr float MAX_WHEEL_DENSITY = 10.0f;
};

#endif  // CONFIG_H
