/**
 * @brief This file contains all the constant values used in the map generation algorithm.
 *
 * @file MapGenConfig.h
 * @author Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef MAPGENCONFIG_H
#define MAPGENCONFIG_H

class MapGenConfig {
   public:
    static constexpr float GENERATE_DISTANCE = 200.0;
    static constexpr float GROUND_STARTING_X = 0.0;
    static constexpr float GROUND_STARTING_Y = 360.0;
    static constexpr float GROUND_LEG_LENGTH = 4.0;
    static constexpr float GROUND_PART_LENGTH = 1.5;
    static constexpr int BG_SPRITES_COUNT = 5;

    static constexpr float CAR_STARTING_X = 250.0;
    static constexpr float CAR_STARTING_Y = 650.0;

    // Change the mapgen behaviour here
    static constexpr float GROUND_DEGREE_DEVIATION = 12.0f;
    static constexpr float MAX_GROUND_DEGREE = 50.0f;


};

#endif  // MAPGENCONFIG_H
