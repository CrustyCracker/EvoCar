/**
 * @brief This file contains all the constant values for the car class.
 *
 * @file CarConfig.h
 * @authors Mateusz Krakowski, Jakub Marcowski
 * @date 2023-06-07
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

    // F = V^2 * k
    // k ≈ 1/2 * ρ * A * C_d ≈ 3.4
    // ρ = 1.293 kg/m^3
    // A = ? (let's assume 5 m^2)
    // C_d = ? (let's assume 1.05)
    //
    // F = 3.4 * V^2
    static constexpr float AIR_RES_FACTOR = 3.4f;
};

#endif  // CARCONFIG_H
