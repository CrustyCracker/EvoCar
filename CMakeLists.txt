cmake_minimum_required(VERSION 3.15)

project(EvoRacer
LANGUAGES CXX
VERSION 0.1.0
)

set(CMAKE_CXX_COMPILER ${CPP_COMPILER})
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(dependencies)
add_subdirectory(test)
add_executable(EvoRacer src/Main.cc)
target_link_libraries(EvoRacer PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML imgui box2d EvoRacerLib)

enable_testing()

 