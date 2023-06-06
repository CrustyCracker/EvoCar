/**
 * @brief File containing GUI functions.
 *
 * @file GUI.cc
 * @author Jakub Marcowski
 * @date 2023-06-06
 */

#include "GUI.h"

void renderVelocityPlot(std::vector<Car>& cars, bool paused) {
    ImGui::Begin("Cars' Velocity");
    ImPlot::SetNextAxesToFit();
    if (ImPlot::BeginPlot("Velocity")) {
        ImPlot::SetupLegend(ImPlotLocation_West, ImPlotLegendFlags_Outside);
        for (int i = 0; i < cars.size(); ++i) {
            char i_str[11];  // 10 digits + null
            sprintf(i_str, "%d", i);

            if (!paused) {
                cars[i].getVelX()->push_back(cars[i].getVelX()->back() + 1);
                cars[i].getVelY()->push_back(cars[i].getVelocity());
            }
            std::vector<float> v_axis_crop = std::vector<float>(
                cars[i].getVelX()->end() - Config::VELOCITY_ARRAY_SIZE, cars[i].getVelX()->end());
            std::vector<float> v_values_crop = std::vector<float>(
                cars[i].getVelY()->end() - Config::VELOCITY_ARRAY_SIZE, cars[i].getVelY()->end());
            ImPlot::PushStyleColor(ImPlotCol_Line, SFMLColorToImVec4(cars[i].getBodyColor()));
            ImPlot::PlotLine(i_str, &(v_axis_crop[0]), &(v_values_crop[0]),
                             Config::VELOCITY_ARRAY_SIZE);
            ImPlot::PopStyleColor();
        }
        ImPlot::EndPlot();
    }
    ImGui::End();
}
