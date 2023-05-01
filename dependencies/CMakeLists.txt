include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY  https://github.com/SFML/SFML
  GIT_TAG         2f11710abc5aa478503a7ff3f9e654bd2078ebab  # 2.5.1
  GIT_SHALLOW     TRUE
  FIND_PACKAGE_ARGS NAMES SFML
)
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY  https://github.com/SFML/imgui-sfml
  GIT_TAG         v2.5
  GIT_SHALLOW     TRUE
  FIND_PACKAGE_ARGS NAMES ImGui-SFML
)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY  https://github.com/ocornut/imgui
  GIT_TAG         35b1148efb839381b84de9290d9caf0b66ad7d03
  GIT_SHALLOW     TRUE
  FIND_PACKAGE_ARGS NAMES ImGui
)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY  https://github.com/google/googletest
  GIT_TAG         release-1.12.1
  GIT_SHALLOW     TRUE
  FIND_PACKAGE_ARGS NAMES GTest
)

FetchContent_MakeAvailable(imgui)
FetchContent_MakeAvailable(googletest)
add_subdirectory(imgui-sfml)
add_subdirectory(sfml)
