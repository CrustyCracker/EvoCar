cmake_minimum_required(VERSION 3.15)

project(EvoRacer
LANGUAGES CXX
VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(dependencies)

add_executable(EvoRacer src/main.cc)
target_link_libraries(EvoRacer PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML imgui box2d EvoRacerLib)

enable_testing()

add_executable(
  box_test
  tests/box_test.cc
)
target_link_libraries(
  box_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(box_test)
