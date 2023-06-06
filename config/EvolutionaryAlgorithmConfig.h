/**
 * @brief This file contains all the constant values used in the evolutionary algorithm.
 *
 * @file EvolutionaryAlgorithmConfig.h
 * @author Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef EVOLUTIONARY_ALGORITHM_CONFIG_H
#define EVOLUTIONARY_ALGORITHM_CONFIG_H

class EvolutionaryAlgorithmConfig {
   public:
    // Evolutionary algorithm parameters
    static constexpr int POPULATION_SIZE = 15;

    // Boundaries for the chromosomes
    static constexpr float MIN_BODY_LENGTH = 1.0f;
    static constexpr float MAX_BODY_LENGTH = 5.0f;

    static constexpr float MIN_BODY_DENSITY = 10.0f;
    static constexpr float MAX_BODY_DENSITY = 1000.0f;

    static constexpr float MIN_WHEEL_RADIUS = 2.0f;
    static constexpr float MAX_WHEEL_RADIUS = 40.0f;

    static constexpr float MIN_WHEEL_DENSITY = 10.0f;
    static constexpr float MAX_WHEEL_DENSITY = 1000.0f;

    // Population initialization hyper parameters
    static constexpr float INITIAL_BODY_LENGTH_MEAN = 3.0f;
    static constexpr float INITIAL_BODY_LENGTH_VARIANCE = 1.0f;

    static constexpr float INITIAL_BODY_DENSITY_MEAN = 100.0f;
    static constexpr float INITIAL_BODY_DENSITY_VARIANCE = 100.0f;

    static constexpr float INITIAL_WHEEL_RADIUS_MEAN = 25.0f;
    static constexpr float INITIAL_WHEEL_RADIUS_VARIANCE = 10.0f;

    static constexpr float INITIAL_WHEEL_DENSITY_MEAN = 100.0f;
    static constexpr float INITIAL_WHEEL_DENSITY_VARIANCE = 100.0f;

    // Mutation hyper parameters

    static constexpr float MUTATION_RATE_BODY_LENGTHS = 0.1f;
    static constexpr float MUTATION_FACTOR_BODY_LENGTHS = 0.5f;

    static constexpr float MUTATION_RATE_BODY_DENSITY = 0.2f;
    static constexpr float MUTATION_FACTOR_BODY_DENSITY = 20.0f;

    static constexpr float MUTATION_RATE_WHEEL_RADIUS = 0.3f;
    static constexpr float MUTATION_FACTOR_WHEEL_RADIUS = 2.0f;

    static constexpr float MUTATION_RATE_WHEEL_DENSITY = 0.1f;
    static constexpr float MUTATION_FACTOR_WHEEL_DENSITY = 20.0f;

    // Selection hyper parameters
    static constexpr int TOURNAMENT_SIZE = 3;  // Has to be equal to or lesser than POPULATION_SIZE
};

#endif  // EVOLUTIONARY_ALGORITHM_CONFIG_H
