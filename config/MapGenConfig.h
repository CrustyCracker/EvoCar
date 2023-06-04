#ifndef MAPGENCONFIG_H
#define MAPGENCONFIG_H

/*
Author: Mateusz Krakowski,
Description: This file contains all the constant values used in the map generation algorithm.
*/

class MapGenConfig {
   public:
    static constexpr int GENERATE_DISTANCE = 200;
    static constexpr int GROUND_STARTING_X = 0;
    static constexpr int GROUND_STARTING_Y = 200;
    static constexpr int GROUND_LEG_LENGTH = 4;
    static constexpr int GROUND_PART_LENGTH = 1;

    // Change the mapgen behaviour here
    static constexpr float GROUND_DEGREE_DEVIATION = 12.0f;
    static constexpr float MAX_GROUND_DEGREE = 50.0f;
};

#endif  // MAPGENCONFIG_H
