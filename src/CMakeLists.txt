set(CXX_CLANG_TIDY)
add_library(EvoRacerLib
Car.cc Car.h
Shape.cc Shape.h
Render.cc Render.h)
target_link_libraries(EvoRacerLib sfml-graphics box2d)
