/**
 * @brief This file contains all the constant values for the car class.
 *
 * @file CarConfig.h
 * @author Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef CARCONFIG_H
#define CARCONFIG_H

class CarConfig {
   public:

       // Car speed is dependent on the car's torque
    static constexpr float CAR_TORQUE = 2000.0f;
    
     
    static constexpr float MAX_JOINT_LENGTH = 0.01f;
    // Number of vertices in a car's body polygon
    static constexpr int CAR_VERTICES = 8;

};

#endif  // CARCONFIG_H
