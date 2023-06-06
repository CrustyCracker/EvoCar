cmake_minimum_required(VERSION 3.22)

project(EvoRacer
    LANGUAGES CXX
    VERSION 0.1.0
)

enable_testing()

set(CMAKE_CXX_COMPILER ${CPP_COMPILER})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

add_compile_definitions(ImDrawIdx=unsigned) # Fix for implot (unsigned = unsigned int)

add_subdirectory(dependencies)
add_subdirectory(src)
add_subdirectory(test)

IF(WIN32)
    add_executable(EvoRacer WIN32 src/Main.cc)
ELSE()
    add_executable(EvoRacer src/Main.cc)
ENDIF()

target_link_libraries(EvoRacer PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML imgui box2d EvoRacerLib nlohmann_json::nlohmann_json implot)
