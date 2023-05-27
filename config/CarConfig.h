#ifndef CARCONFIG_H
#define CARCONFIG_H

/*
Author: Mateusz Krakowski, 
Description: This file contains all the constant values for the car class.
*/

class Config {
   public:

    static constexpr float MAX_JOINT_LENGTH = 0.01f;

    // Number of vertices in a car's body polygon
    static constexpr int CAR_VERTICES = 8;

};
#endif  // CARCONFIG_H
