set(CXX_CLANG_TIDY)
add_executable(EvoRacer main.cc)
add_library(EvoRacerLib
box.cc box.h
car.cc car.h
circle.cc circle.h
polygon.cc polygon.h
render.cc render.h)
target_link_libraries(EvoRacer PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML imgui box2d EvoRacerLib)

