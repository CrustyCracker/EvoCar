#include <gtest/gtest.h>
#include "../src/EvolutionaryAlgorithm.h"
/*
Author: Mateusz Krakowski
Description: This file contains tests for functions from src/EvolutionaryAlgorithm.h.
*/
TEST(EvolutionaryAlgorithmTest, MutationTest) {
    EvolutionaryAlgorithm evo(10);
    // mutate the genes 50 times just to test it
    for (int i = 0; i < 50; ++i) {
        evo.mutate();
    }
    std::vector<Chromosome> genes = evo.getPopulation();

    // assert that all body lengths are within the range
    for (auto& chrom : genes) {
        for (auto& length : chrom.bodyLengths) {
            ASSERT_GE(length, EvolutionaryAlgorithmConfig::MIN_BODY_LENGTH);
            ASSERT_LE(length, EvolutionaryAlgorithmConfig::MAX_BODY_LENGTH);
        }
    }
}

TEST(EvolutionaryAlgorithmTest, TournamentSelectionTest) {
    EvolutionaryAlgorithm evo(10);
    evo.tournamentSelection();
    std::vector<Chromosome> genes = evo.getPopulation();

    ASSERT_TRUE(genes.size() == 10);
}

TEST(EvolutionaryAlgorithmTest, NextGenerationTest) {
    EvolutionaryAlgorithm evo(10);
    evo.nextStep();
    for(int i = 0; i < 10; ++i) {
        evo.nextGeneration();
    }

    std::vector<Chromosome> genes = evo.getPopulation();

    ASSERT_TRUE(genes.size() == 10);
    ASSERT_TRUE(evo.getGeneration() == 10);
}
