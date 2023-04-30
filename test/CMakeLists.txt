add_executable(
  Tests
  ShapeTest.cc
)
target_link_libraries(Tests GTest::gtest_main sfml-graphics ImGui-SFML::ImGui-SFML imgui box2d EvoRacerLib)

include(GoogleTest)
gtest_discover_tests(Tests)