include(FetchContent)
find_library(SFML_LIB sfml-graphics)
find_library(SFML_WINDOW sfml-window)
find_library(GTEST_LIB gtest)
find_library(GTEST_MAIN_LIB gtest_main)
find_library(IMGUI_LIB imgui)

FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml
  GIT_TAG v2.5
  GIT_SHALLOW TRUE
  FIND_PACKAGE_ARGS NAMES ImGui-SFML
)

add_subdirectory(imgui-sfml)
