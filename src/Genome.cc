#include "Genome.h"

/*
Author:         Mateusz Krakowski
Description:    Creates a genome with a population of genes. Needed in evolutionary algorithm.
*/

EvolutionaryAlgorithm::EvolutionaryAlgorithm(int populationSize) {
    populationSize_ = populationSize;
    generation_ = 0;
    for (int i = 0; i < populationSize_; ++i) {
        Individual gene;
        gene.bodyLengths = { 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f };
        gene.bodyDensity = 1.0f;
        gene.wheelRadius = { 0.2f, 0.2f };
        gene.wheelDensity = { 1.0f, 1.0f };
        gene.fitness = 0.0f;
        genes_.push_back(gene);
    }
}

void EvolutionaryAlgorithm::mutate() {
    // Define the mutation rates for different attributes
    const float mutationRateBodyLengths = 0.1;
    const float mutationRateBodyDensity = 0.05;
    const float mutationRateWheelRadius = 0.2;
    const float mutationRateWheelDensity = 0.1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0, 1.0);

    for (auto& gene : genes_) {
        // Mutate bodyLengths
        for (auto& length : gene.bodyLengths) {
            if (dist(gen) < mutationRateBodyLengths) {
                length += dist(gen);
                length = std::max(length, Config::MIN_BODY_LENGTH);
                length = std::min(length, Config::MAX_BODY_LENGTH);
            }
        }

        // Mutate bodyDensity
        if (dist(gen) < mutationRateBodyDensity) {
            gene.bodyDensity += dist(gen);
            gene.bodyDensity = std::max(0.0f, gene.bodyDensity);  // Ensure it doesn't go below 0
            // Adjust the maximum value if needed
            // gene.bodyDensity = std::min(gene.bodyDensity, MAX_VALUE);
        }

        // Mutate wheelRadius
        if (dist(gen) < mutationRateWheelRadius) {
            gene.wheelRadius.first += dist(gen);
            gene.wheelRadius.first = std::max(0.0f, gene.wheelRadius.first);  // Ensure it doesn't go below 0
            // Adjust the maximum value if needed
            // gene.wheelRadius.first = std::min(gene.wheelRadius.first, MAX_VALUE);

            gene.wheelRadius.second += dist(gen);
            gene.wheelRadius.second = std::max(0.0f, gene.wheelRadius.second);  // Ensure it doesn't go below 0
            // Adjust the maximum value if needed
            // gene.wheelRadius.second = std::min(gene.wheelRadius.second, MAX_VALUE);
        }

        // Mutate wheelDensity
        if (dist(gen) < mutationRateWheelDensity) {
            gene.wheelDensity.first += dist(gen);
            gene.wheelDensity.first = std::max(0.0f, gene.wheelDensity.first);  // Ensure it doesn't go below 0
            // Adjust the maximum value if needed
            // gene.wheelDensity.first = std::min(gene.wheelDensity.first, MAX_VALUE);

            gene.wheelDensity.second += dist(gen);
            gene.wheelDensity.second = std::max(0.0f, gene.wheelDensity.second);  // Ensure it doesn't go below 0
            // Adjust the maximum value if needed
            // gene.wheelDensity.second = std::min(gene.wheelDensity.second, MAX_VALUE);
        }
    }
}

void EvolutionaryAlgorithm::crossover() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, populationSize_ - 1);

    std::vector<Individual> offspring(populationSize_);

    for (int i = 0; i < populationSize_; i++) {
        int parentIndex1 = dist(gen);
        int parentIndex2 = dist(gen);

        // Perform crossover between parent genes
        Individual& parent1 = genes_[parentIndex1];
        Individual& parent2 = genes_[parentIndex2];
        Individual& child = offspring[i];

        // Perform crossover for bodyLengths
        int crossoverPoint = dist(gen);
        child.bodyLengths.insert(child.bodyLengths.end(), parent1.bodyLengths.begin(), parent1.bodyLengths.begin() + crossoverPoint);
        child.bodyLengths.insert(child.bodyLengths.end(), parent2.bodyLengths.begin() + crossoverPoint, parent2.bodyLengths.end());

        // Perform crossover for other attributes
        child.bodyDensity = (parent1.bodyDensity + parent2.bodyDensity) / 2.0;
        child.wheelRadius = std::make_pair((parent1.wheelRadius.first + parent2.wheelRadius.first) / 2.0,
                                           (parent1.wheelRadius.second + parent2.wheelRadius.second) / 2.0);
        child.wheelDensity = std::make_pair((parent1.wheelDensity.first + parent2.wheelDensity.first) / 2.0,
                                            (parent1.wheelDensity.second + parent2.wheelDensity.second) / 2.0);
    }

    // Replace the old generation with the offspring
    genes_ = offspring;
    generation_++;
}