add_executable(EvoRacer main.cc)
target_link_libraries(EvoRacer PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML imgui box2d)

