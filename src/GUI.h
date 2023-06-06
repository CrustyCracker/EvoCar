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

#endif  // GUI_H
