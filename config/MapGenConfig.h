#ifndef MAPGENCONFIG_H
#define MAPGENCONFIG_H

/*
Author: Mateusz Krakowski,
Description: This file contains all the constant values used in the map generation algorithm.
*/

class MapGenConfig {
   public:
    static constexpr float GENERATE_DISTANCE = 200.0;
    static constexpr float GROUND_STARTING_X = 0.0;
    static constexpr float GROUND_STARTING_Y = 200.0;
    static constexpr float GROUND_LEG_LENGTH = 4.0;
    static constexpr float GROUND_PART_LENGTH = 1.5;

    static constexpr float CAR_STARTING_X = 250.0;
    static constexpr float CAR_STARTING_Y = 500.0;

    // Change the mapgen behaviour here
    static constexpr float GROUND_DEGREE_DEVIATION = 12.0f;
    static constexpr float MAX_GROUND_DEGREE = 50.0f;
};

#endif  // MAPGENCONFIG_H
