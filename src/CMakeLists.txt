set(CXX_CLANG_TIDY)
add_library(EvoRacerLib
  Car.cc Car.h
  Shape.cc Shape.h
  Render.cc Render.h
  EvolutionaryAlgorithm.cc EvolutionaryAlgorithm.h)

IF(WIN32)
  add_dependencies(EvoRacerLib box2d)
ENDIF()

target_link_libraries(EvoRacerLib sfml-graphics box2d)
