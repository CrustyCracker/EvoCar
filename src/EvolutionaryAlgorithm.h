/*
Author:         Mateusz Krakowski
Description:    Header file for EvolutionaryAlgorithm class.
*/

#ifndef GENOME_H
#define GENOME_H
#include <vector>
#include <random>
#include "../config/Config.h"
#include "../config/EvolutionaryAlgorithmConfig.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <deque>

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
    bool saveToFile_ = false;
    Chromosome tournament();
    void initializePopulation();

   public:
    EvolutionaryAlgorithm(int populationSize, bool saveToFile = false);
    std::vector<Chromosome> getPopulation() { return population_; }
    void mutate();
    void tournamentSelection();
    void nextGeneration();
    void setFitness(int index, float fitness) { population_[index].fitness = fitness; }
    int getGeneration() { return generation_; }
    int getPopulationSize() { return populationSize_; }
    int exportPopulation();
};

#endif