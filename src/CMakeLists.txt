set(CXX_CLANG_TIDY)
add_library(EvoRacerLib
  Car.cc Car.h
  Shape.cc Shape.h
  Render.cc Render.h
  EvolutionaryAlgorithm.cc EvolutionaryAlgorithm.h
  Utility.cc Utility.h
  UserInput.cc UserInput.h)

IF(WIN32)
  add_dependencies(EvoRacerLib box2d)
ENDIF()

target_link_libraries(EvoRacerLib sfml-graphics ImGui-SFML::ImGui-SFML box2d nlohmann_json::nlohmann_json)
target_include_directories(EvoRacerLib PRIVATE ${imgui_SOURCE_DIR})
target_include_directories(EvoRacerLib PRIVATE ${imgui-sfml_SOURCE_DIR})
