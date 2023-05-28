#include <gtest/gtest.h>
#include "../src/EvolutionaryAlgorithm.h"
/*
Author: Mateusz Krakowski
Description: This file contains tests for functions from src/EvolutionaryAlgorithm.h.
*/
TEST(EvolutionaryAlgorithmTest, MutationTest) {
    EvolutionaryAlgorithm evo(10);
    // mutate the population 50 times just to test it
    for (int i = 0; i < 50; ++i) {
        evo.mutate();
    }
    std::vector<Chromosome> population = evo.getPopulation();

    // assert that all body lengths are within the range
    for (auto& chrom : population) {
        for (auto& length : chrom.bodyLengths) {
            ASSERT_GE(length, EvolutionaryAlgorithmConfig::MIN_BODY_LENGTH);
            ASSERT_LE(length, EvolutionaryAlgorithmConfig::MAX_BODY_LENGTH);
        }
    }
}

TEST(EvolutionaryAlgorithmTest, TournamentSelectionTest) {
    EvolutionaryAlgorithm evo(10);
    evo.tournamentSelection();
    std::vector<Chromosome> population = evo.getPopulation();

    ASSERT_EQ(population.size(), 10);
}

TEST(EvolutionaryAlgorithmTest, NextGenerationTest) {
    EvolutionaryAlgorithm evo(10);
    evo.nextGeneration();
    for (int i = 0; i < 49; ++i) {
        evo.nextGeneration();
    }

    ASSERT_EQ(evo.getGeneration(), 50);
}
