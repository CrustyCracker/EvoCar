include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY "https://github.com/SFML/SFML"
  GIT_TAG 2f11710abc5aa478503a7ff3f9e654bd2078ebab # 2.5.1
) 
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml
  GIT_TAG v2.5
)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG 35b1148efb839381b84de9290d9caf0b66ad7d03
)


FetchContent_MakeAvailable(imgui)
add_subdirectory(imgui-sfml)
add_subdirectory(sfml)