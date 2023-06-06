add_executable(
  Test
  ShapeTest.cc
  EvolutionaryAlgorithmTest.cc
  CarTest.cc
  UtilityTest.cc
)

IF(WIN32)
  add_dependencies(Test box2d)
ENDIF()

target_link_libraries(Test GTest::gtest_main sfml-graphics ImGui-SFML::ImGui-SFML imgui box2d EvoRacerLib)
add_test(NAME ShapeTest COMMAND Test)
add_test(NAME EvolutionaryAlgorithmTest COMMAND Test)
add_test(NAME CarTest COMMAND Test)
add_test(NAME UtilityTest COMMAND Test)

include(GoogleTest)
gtest_discover_tests(Test)
