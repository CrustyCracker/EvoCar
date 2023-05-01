set(CXX_CLANG_TIDY)
add_library(EvoRacerLib
Car.cc Car.h
Shape.cc Shape.h
Render.cc Render.h)
add_dependencies (EvoRacerLib box2d)
target_link_libraries(EvoRacerLib sfml-graphics box2d)
