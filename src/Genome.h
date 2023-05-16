/*
Author:         Mateusz Krakowski
Description:    Header file for EvolutionaryAlgorithm class needed for evolutionary algorithm.
*/

#ifndef GENOME_H
#define GENOME_H
#include <vector>
#include <random>
#include "../config/Config.h"

struct Individual
{
    std::vector<float> bodyLengths;
    float bodyDensity;
    std::pair<float, float> wheelRadius;
    std::pair<float, float> wheelDensity;
    float fitness;
};


class EvolutionaryAlgorithm
{
private:
    int generation_;
    int populationSize_;
    std::vector<Individual> genes_{populationSize_};
public:
    EvolutionaryAlgorithm(int populationSize);
    std::vector<Individual> getGenes() { return genes_; }
    void mutate();
    void crossover();
    void setFitness(int index, float fitness) { genes_[index].fitness = fitness; }

};

#endif