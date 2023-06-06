/**
 * @brief Header for a file containing GUI functions.
 *
 * @file GUI.h
 * @author Jakub Marcowski
 * @date 2023-06-06
 */

#ifndef GUI_H
#define GUI_H

#include <vector>

#include "imgui.h"
#include "implot.h"

#include "Car.h"
#include "EvolutionaryAlgorithm.h"
#include "Utility.h"

/**
 * @brief Renders velocity plot.
 * @param cars Vector of cars.
 * @param paused Whether or not simulation is paused.
 */
void renderVelocityPlot(std::vector<Car>& cars, bool paused);

/**
 * @brief Renders position plot.
 *
 * @param cars Vector of cars.
 * @param paused Whether or not simulation is paused.
 */
void renderPositionPlot(std::vector<Car>& cars, bool paused);

/**
 * @brief Renders Evolutionary Algorithm's inner state.
 *
 * @param ea Evolutionary Algorithm object.
 */
void printEAInfo(EvolutionaryAlgorithm& ea);

#endif  // GUI_H
