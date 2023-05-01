add_executable(
  Test
  ShapeTest.cc
)
target_link_libraries(Test GTest::gtest_main sfml-graphics ImGui-SFML::ImGui-SFML imgui box2d EvoRacerLib)
add_test(NAME ShapeTest COMMAND Test)

include(GoogleTest)
gtest_discover_tests(Test)
