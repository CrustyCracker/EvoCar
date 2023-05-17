/*
Author:         Mateusz Krakowski
Description:    Header file for EvolutionaryAlgorithm class needed for evolutionary algorithm.
*/

#ifndef GENOME_H
#define GENOME_H
#include <vector>
#include <random>
#include "../config/EvolutionaryAlgorithmConfig.h"

struct Chromosome {
    std::vector<float> bodyLengths;
    float bodyDensity;
    std::pair<float, float> wheelRadius;
    std::pair<float, float> wheelDensity;
    float fitness;
};

class EvolutionaryAlgorithm {
   private:
    unsigned long int generation_;
    unsigned long int populationSize_;
    std::vector<Chromosome> population_{populationSize_};

   public:
    EvolutionaryAlgorithm(int populationSize);
    std::vector<Chromosome> getGenes() { return population_; }
    void mutate();
    void crossover();
    void setFitness(int index, float fitness) { population_[index].fitness = fitness; }

    int getGeneration() { return generation_; }
    int getPopulationSize() { return populationSize_; }
};

#endif