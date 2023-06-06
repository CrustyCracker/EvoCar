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
#include "../config/CarConfig.h"

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
    /**
     * @brief performs tournament selection on the population
     * @return the winner of the tournament
     */
    Chromosome tournament();
    /**
     * @brief initializes the population
     */
    void initializePopulation();

   public:
    /**
     * @brief Construct a new Evolutionary Algorithm:: Evolutionary Algorithm object
     *
     * @param populationSize  The size of the population
     * @param saveToFile    Whether to save the population to a file
     */
    explicit EvolutionaryAlgorithm(int populationSize, bool saveToFile = false);
    std::vector<Chromosome> getPopulation() { return population_; }
    /**
     * @brief mutates the population
     */
    void mutate();
    /**
     * @brief performs tournament selection on the population
     */
    void tournamentSelection();
    /**
     * @brief steps the algorithm to the next generation
     */
    void nextGeneration();
    void setFitness(int index, float fitness) { population_[index].fitness = fitness; }
    int getGeneration() const { return generation_; }
    int getPopulationSize() const { return populationSize_; }
    /**
     * @brief exports the population to a json file
     */
    int exportPopulation();
};

#endif
