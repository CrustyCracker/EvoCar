cmake_minimum_required(VERSION 3.22)

find_library(box2d REQIRED)

project(EvoRacer
    LANGUAGES CXX
    VERSION 0.1.0
)
enable_testing()
set(CMAKE_CXX_COMPILER ${CPP_COMPILER})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
add_subdirectory(src)
add_subdirectory(dependencies)
add_subdirectory(test)
add_executable(EvoRacer src/Main.cc)
target_link_libraries(EvoRacer PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML imgui box2d EvoRacerLib json)
