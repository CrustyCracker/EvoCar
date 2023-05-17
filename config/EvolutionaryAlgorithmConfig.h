#ifndef EVOLUTIONARY_ALGORITHM_CONFIG_H
#define EVOLUTIONARY_ALGORITHM_CONFIG_H

/*
Author: Mateusz Krakowski
Description: This file contains all the constant values used in the evolutionary algorithm.
*/

class EvolutionaryAlgorithmConfig {
   public:

    // Evolutionary algorithm parameters
    static constexpr int POPULATION_SIZE = 10;

    static constexpr float MIN_BODY_LENGTH = 1.0f;
    static constexpr float MAX_BODY_LENGTH = 10.0f;
    static constexpr float MUTATION_RATE_BODY_LENGTHS = 0.1f;
    static constexpr float MUTATION_FACTOR_BODY_LENGTHS = 0.1f;
    
    static constexpr float MIN_BODY_DENSITY = 0.1f;
    static constexpr float MAX_BODY_DENSITY = 10.0f;
    static constexpr float MUTATION_RATE_BODY_DENSITY = 0.05f;
    static constexpr float MUTATION_FACTOR_BODY_DENSITY = 0.1f;

    static constexpr float MIN_WHEEL_RADIUS = 0.1f;
    static constexpr float MAX_WHEEL_RADIUS = 1.0f;
    static constexpr float MUTATION_RATE_WHEEL_RADIUS = 0.2f;
    static constexpr float MUTATION_FACTOR_WHEEL_RADIUS = 0.1f;

    static constexpr float MIN_WHEEL_DENSITY = 0.1f;
    static constexpr float MAX_WHEEL_DENSITY = 10.0f;
    static constexpr float MUTATION_RATE_WHEEL_DENSITY = 0.1f;
    static constexpr float MUTATION_FACTOR_WHEEL_DENSITY = 0.1f;
};

#endif  // EVOLUTIONARY_ALGORITHM_CONFIG_H
