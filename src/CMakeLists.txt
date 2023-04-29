add_executable(EvoRacer main.cc)
target_link_libraries(EvoRacer PRIVATE sfml-graphics)
target_link_libraries(EvoRacer PRIVATE ImGui-SFML::ImGui-SFML)
target_link_libraries(EvoRacer PRIVATE imgui)
target_link_libraries(EvoRacer PRIVATE box2d)

