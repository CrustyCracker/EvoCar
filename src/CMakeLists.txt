set(CXX_CLANG_TIDY)
add_executable(EvoRacer main.cc)
add_library(EvoRacerLib
    car.cc  car.h
    box.cc  box.h
    circle.cc circle.h
    poligon.cc poligon.h
    render.cc   render.h)
target_link_libraries(EvoRacer PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML imgui box2d EvoRacerLib)

