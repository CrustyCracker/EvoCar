/**
 * @brief Implementation file for EvolutionaryAlgorithm
 * class, Algorithm used for evolving the cars.
 *
 * @file EvolutionaryAlgorithm.cc
 * @author Mateusz Krakowski
 * @date 2023-06-06
 */

#include "EvolutionaryAlgorithm.h"

EvolutionaryAlgorithm::EvolutionaryAlgorithm(int populationSize, bool saveToFile) {
    populationSize_ = populationSize;
    generation_ = 0;
    initializePopulation();
    saveToFile_ = saveToFile;
}

void EvolutionaryAlgorithm::initializePopulation() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(0.0, 1.0);
    // add variation and mean
    for (int i = 0; i < populationSize_; ++i) {
        Chromosome chrom;
        // MKTODO czange the 8
        for (int p = 0; p < 8; ++p) {
            float length = dist(gen) * EvolutionaryAlgorithmConfig::INITIAL_BODY_LENGTH_VARIANCE +
                           EvolutionaryAlgorithmConfig::INITIAL_BODY_LENGTH_MEAN;
            length = std::max(length, EvolutionaryAlgorithmConfig::MIN_BODY_LENGTH);
            length = std::min(length, EvolutionaryAlgorithmConfig::MAX_BODY_LENGTH);
            chrom.bodyLengths.push_back(length);
        }

        // Initialize bodyDensity

        chrom.bodyDensity = dist(gen) * EvolutionaryAlgorithmConfig::INITIAL_BODY_DENSITY_VARIANCE +
                            EvolutionaryAlgorithmConfig::INITIAL_BODY_DENSITY_MEAN;

        chrom.bodyDensity =
            std::max(chrom.bodyDensity, EvolutionaryAlgorithmConfig::MIN_BODY_DENSITY);
        chrom.bodyDensity =
            std::min(chrom.bodyDensity, EvolutionaryAlgorithmConfig::MAX_BODY_DENSITY);

        // initialize wheelRadius

        chrom.wheelRadius.first =
            dist(gen) * EvolutionaryAlgorithmConfig::INITIAL_WHEEL_RADIUS_VARIANCE +
            EvolutionaryAlgorithmConfig::INITIAL_WHEEL_RADIUS_MEAN;
        chrom.wheelRadius.first =
            std::max(chrom.wheelRadius.first, EvolutionaryAlgorithmConfig::MIN_WHEEL_RADIUS);
        chrom.wheelRadius.first =

            chrom.wheelRadius.second +=
            dist(gen) * EvolutionaryAlgorithmConfig::INITIAL_WHEEL_RADIUS_VARIANCE +
            EvolutionaryAlgorithmConfig::INITIAL_WHEEL_RADIUS_MEAN;
        chrom.wheelRadius.second =
            std::max(chrom.wheelRadius.second, EvolutionaryAlgorithmConfig::MIN_WHEEL_RADIUS);
        chrom.wheelRadius.second =
            std::min(chrom.wheelRadius.second, EvolutionaryAlgorithmConfig::MAX_WHEEL_RADIUS);

        // Initialize wheelDensity

        chrom.wheelDensity.first +=
            dist(gen) * EvolutionaryAlgorithmConfig::INITIAL_WHEEL_DENSITY_VARIANCE +
            EvolutionaryAlgorithmConfig::INITIAL_WHEEL_DENSITY_MEAN;
        chrom.wheelDensity.first =
            std::max(chrom.wheelDensity.first, EvolutionaryAlgorithmConfig::MIN_WHEEL_DENSITY);
        chrom.wheelDensity.first =
            std::min(chrom.wheelDensity.first, EvolutionaryAlgorithmConfig::MAX_WHEEL_DENSITY);

        chrom.wheelDensity.second +=
            dist(gen) * EvolutionaryAlgorithmConfig::INITIAL_WHEEL_DENSITY_VARIANCE +
            EvolutionaryAlgorithmConfig::INITIAL_WHEEL_DENSITY_MEAN;
        chrom.wheelDensity.second =
            std::max(chrom.wheelDensity.second, EvolutionaryAlgorithmConfig::MIN_WHEEL_DENSITY);
        chrom.wheelDensity.second =
            std::min(chrom.wheelDensity.second, EvolutionaryAlgorithmConfig::MAX_WHEEL_DENSITY);

        population_.push_back(chrom);
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
    if (saveToFile_) {
        exportPopulation();
    }
    tournamentSelection();
    mutate();
    ++generation_;
}

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

    std::ofstream outputFile(EvolutionaryAlgorithmConfig::SAVE_FILE_NAME, std::ios::app);
    if (!outputFile.is_open()) {
        return 1;
    }
    outputFile << jsonString;
    outputFile.close();

    return 0;
}
