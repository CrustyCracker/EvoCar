#include "EvolutionaryAlgorithm.h"

/*
Author:         Mateusz Krakowski
Description:    Implementation file for EvolutionaryAlgorithm class, Algorithm used for evolving the
                cars.
*/

EvolutionaryAlgorithm::EvolutionaryAlgorithm(int populationSize) {
    populationSize_ = populationSize;
    generation_ = 0;
    for (int i = 0; i < populationSize_; ++i) {
        Chromosome chrom;
        chrom.bodyLengths = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
        chrom.bodyDensity = 100.0f;
        chrom.wheelRadius = {25.0f, 25.0f};
        chrom.wheelDensity = {100.0f, 100.0f};
        chrom.fitness = 0.0f;
        population_.push_back(chrom);
    }

    // MKTODO: For now, spice it up by mutating cuple of times :)
    for (int i = 0; i < 10; ++i) {
        mutate();
    }
}

void EvolutionaryAlgorithm::mutate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(0.0, 1.0);

    for (auto& chrom : population_) {
        // Mutate bodyLengths
        for (auto& length : chrom.bodyLengths) {
            if (dist(gen) < EvolutionaryAlgorithmConfig::MUTATION_RATE_BODY_LENGTHS) {
                length += dist(gen) * EvolutionaryAlgorithmConfig::MUTATION_FACTOR_BODY_LENGTHS;
                length = std::max(length, EvolutionaryAlgorithmConfig::MIN_BODY_LENGTH);
                length = std::min(length, EvolutionaryAlgorithmConfig::MAX_BODY_LENGTH);
            }
        }

        // Mutate bodyDensity
        if (dist(gen) < EvolutionaryAlgorithmConfig::MUTATION_RATE_BODY_DENSITY) {
            chrom.bodyDensity +=
                dist(gen) * EvolutionaryAlgorithmConfig::MUTATION_FACTOR_BODY_DENSITY;

            chrom.bodyDensity =
                std::max(chrom.bodyDensity, EvolutionaryAlgorithmConfig::MIN_BODY_DENSITY);
            chrom.bodyDensity =
                std::min(chrom.bodyDensity, EvolutionaryAlgorithmConfig::MAX_BODY_DENSITY);
        }

        // Mutate wheelRadius
        if (dist(gen) < EvolutionaryAlgorithmConfig::MUTATION_RATE_WHEEL_RADIUS) {
            chrom.wheelRadius.first +=
                dist(gen) * EvolutionaryAlgorithmConfig::MUTATION_FACTOR_WHEEL_RADIUS;
            chrom.wheelRadius.first =
                std::max(chrom.wheelRadius.first, EvolutionaryAlgorithmConfig::MIN_WHEEL_RADIUS);
            chrom.wheelRadius.first =
                std::min(chrom.wheelRadius.first, EvolutionaryAlgorithmConfig::MAX_WHEEL_RADIUS);
        }
        if (dist(gen) < EvolutionaryAlgorithmConfig::MUTATION_RATE_WHEEL_RADIUS) {
            chrom.wheelRadius.second +=
                dist(gen) * EvolutionaryAlgorithmConfig::MUTATION_FACTOR_WHEEL_RADIUS;
            chrom.wheelRadius.second =
                std::max(chrom.wheelRadius.second, EvolutionaryAlgorithmConfig::MIN_WHEEL_RADIUS);
            chrom.wheelRadius.second =
                std::min(chrom.wheelRadius.second, EvolutionaryAlgorithmConfig::MAX_WHEEL_RADIUS);
        }

        // Mutate wheelDensity
        if (dist(gen) < EvolutionaryAlgorithmConfig::MUTATION_RATE_WHEEL_DENSITY) {
            chrom.wheelDensity.first +=
                dist(gen) * EvolutionaryAlgorithmConfig::MUTATION_FACTOR_WHEEL_DENSITY;
            chrom.wheelDensity.first =
                std::max(chrom.wheelDensity.first, EvolutionaryAlgorithmConfig::MIN_WHEEL_DENSITY);
            chrom.wheelDensity.first =
                std::min(chrom.wheelDensity.first, EvolutionaryAlgorithmConfig::MAX_WHEEL_DENSITY);
        }
        if (dist(gen) < EvolutionaryAlgorithmConfig::MUTATION_RATE_WHEEL_DENSITY) {
            chrom.wheelDensity.second +=
                dist(gen) * EvolutionaryAlgorithmConfig::MUTATION_FACTOR_WHEEL_DENSITY;
            chrom.wheelDensity.second =
                std::max(chrom.wheelDensity.second, EvolutionaryAlgorithmConfig::MIN_WHEEL_DENSITY);
            chrom.wheelDensity.second =
                std::min(chrom.wheelDensity.second, EvolutionaryAlgorithmConfig::MAX_WHEEL_DENSITY);
        }
    }
}
Chromosome EvolutionaryAlgorithm::tournament() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> uniform_dist(0, populationSize_ - 1);

    std::vector<Chromosome> candidates;

    for (int i = 0; i < EvolutionaryAlgorithmConfig::TOURNAMENT_SIZE; ++i) {
        candidates.push_back(population_[uniform_dist(gen)]);
    }

    Chromosome tournament_winner = candidates[0];

    for (int i = 1; i < EvolutionaryAlgorithmConfig::TOURNAMENT_SIZE; ++i) {
        if (candidates[i].fitness > tournament_winner.fitness) {
            tournament_winner = candidates[i];
        }
    }

    return tournament_winner;
}
void EvolutionaryAlgorithm::tournamentSelection() {
    std::vector<Chromosome> tournament_winners;

    for (int i = 0; i < populationSize_; ++i) {
        tournament_winners.push_back(tournament());
    }

    population_ = tournament_winners;
}

void EvolutionaryAlgorithm::nextGeneration() {
    exportPopulation();
    tournamentSelection();
    mutate();
    ++generation_;
}

// void EvolutionaryAlgorithm::crossover() {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<int> dist(0, populationSize_ - 1);

//     std::vector<Chromosome> offspring(populationSize_);

//     for (int i = 0; i < populationSize_; i++) {
//         int parentIndex1 = dist(gen);
//         int parentIndex2 = dist(gen);

//         // Perform crossover between parent genes
//         Chromosome& parent1 = population_[parentIndex1];
//         Chromosome& parent2 = population_[parentIndex2];
//         Chromosome& child = offspring[i];

//         // Perform crossover for bodyLengths
//         int crossoverPoint = dist(gen);
//         child.bodyLengths.insert(child.bodyLengths.end(), parent1.bodyLengths.begin(),
//                                  parent1.bodyLengths.begin() + crossoverPoint);
//         child.bodyLengths.insert(child.bodyLengths.end(),
//                                  parent2.bodyLengths.begin() + crossoverPoint,
//                                  parent2.bodyLengths.end());

//         // Perform crossover for other attributes
//         child.bodyDensity = (parent1.bodyDensity + parent2.bodyDensity) / 2.0;
//         child.wheelRadius =
//             std::make_pair((parent1.wheelRadius.first + parent2.wheelRadius.first) / 2.0,
//                            (parent1.wheelRadius.second + parent2.wheelRadius.second) / 2.0);
//         child.wheelDensity =
//             std::make_pair((parent1.wheelDensity.first + parent2.wheelDensity.first) / 2.0,
//                            (parent1.wheelDensity.second + parent2.wheelDensity.second) / 2.0);
//     }

//     // Replace the old generation with the offspring
//     population_ = offspring;
//}

int EvolutionaryAlgorithm::exportPopulation() {
    nlohmann::json jsonData;
    jsonData["generation"] = generation_;

    std::deque<nlohmann::json> populationData;

    for (const auto& chromosome : population_) {
        nlohmann::json chromosomeJson;
        chromosomeJson["bodyLengths"] = chromosome.bodyLengths;
        chromosomeJson["bodyDensity"] = chromosome.bodyDensity;
        chromosomeJson["wheelRadius"] = {chromosome.wheelRadius.first,
                                         chromosome.wheelRadius.second};
        chromosomeJson["wheelDensity"] = {chromosome.wheelDensity.first,
                                          chromosome.wheelDensity.second};
        chromosomeJson["fitness"] = chromosome.fitness;
        populationData.push_front(chromosomeJson);
    }

    jsonData["population"] = populationData;

    std::string jsonString = jsonData.dump(4);

    std::ofstream outputFile("evoRacerOutput.json", std::ios::app);
    if (!outputFile.is_open()) {
        return 1;
    }
    outputFile << jsonString;
    outputFile.close();

    return 0;
}
