include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY  https://github.com/SFML/SFML
  GIT_TAG         2f11710abc5aa478503a7ff3f9e654bd2078ebab  # 2.5.1
  # FIND_PACKAGE_ARGS NAMES SFML
)
FetchContent_Declare(
  box2d
  GIT_REPOSITORY  https://github.com/erincatto/box2d
  GIT_TAG         9ebbbcd960ad424e03e5de6e66a40764c16f51bc  # v2.4.1
  # FIND_PACKAGE_ARGS NAMES Box2D
)
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY  https://github.com/SFML/imgui-sfml
  GIT_TAG         v2.5
  # FIND_PACKAGE_ARGS NAMES ImGui-SFML
)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY  https://github.com/ocornut/imgui
  GIT_TAG         35b1148efb839381b84de9290d9caf0b66ad7d03
  # FIND_PACKAGE_ARGS NAMES ImGui
)
FetchContent_Declare(
  googletest  # how about we change it to git instead of url?
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  # FIND_PACKAGE_ARGS NAMES GTest
)

add_subdirectory(box2d)
FetchContent_MakeAvailable(imgui)
FetchContent_MakeAvailable(googletest)
add_subdirectory(imgui-sfml)
add_subdirectory(sfml)
