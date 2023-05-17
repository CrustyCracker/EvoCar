#include <gtest/gtest.h>
#include "../src/EvolutionaryAlgorithm.h"
/*
Author: Mateusz Krakowski
Description: This file contains tests for functions from src/Shape.h.
*/
typedef std::shared_ptr<b2WorldPtr> b2WorldPtrPtr;
TEST(CreateBoxTest, BasicTest) {
    EvolutionaryAlgorithm evo(10);
    // mutate the genes 50 times just to test it
    for (int i = 0; i < 50; ++i)
    {
        evo.mutate();
    }
    std::vector<Chromosome> genes = evo.getGenes();

    // assert that all body lengths are within the range
    for (auto& chrom : genes) {
        for (auto& length : chrom.bodyLengths) {
            ASSERT_GE(length, EvolutionaryAlgorithmConfig::MIN_BODY_LENGTH);
            ASSERT_LE(length, EvolutionaryAlgorithmConfig::MAX_BODY_LENGTH);
        }
    }
}
