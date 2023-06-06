/**
 * @brief Header file for EvolutionaryAlgorithm class.
 *
 * @file EvolutionaryAlgorithm.h
 * @author Mateusz Krakowski
 * @date 2023-06-06
 */

#ifndef GENOME_H
#define GENOME_H

#include <deque>
#include <fstream>
#include <nlohmann/json.hpp>
#include <random>
#include <vector>

#include "../config/Config.h"
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
