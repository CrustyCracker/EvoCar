/*
Author:         Mateusz Krakowski
Description:    Header file for EvolutionaryAlgorithm class.
*/

#ifndef GENOME_H
#define GENOME_H
#include <vector>
#include <random>
#include "../config/EvolutionaryAlgorithmConfig.h"
#include <nlohmann/json.hpp>

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
    std::vector<Chromosome> population_;
    Chromosome tournament();

   public:
    EvolutionaryAlgorithm(int populationSize);
    std::vector<Chromosome> getPopulation() { return population_; }
    void mutate();
    void tournamentSelection();
    void nextGeneration();
    // void crossover();
    void setFitness(int index, float fitness) { population_[index].fitness = fitness; }
    int getGeneration() { return generation_; }
    int getPopulationSize() { return populationSize_; }
    void exportPopulation();
};

#endif