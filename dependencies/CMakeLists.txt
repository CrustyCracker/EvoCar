include(FetchContent)

set(SFML_VERSION 2.5.1)
set(IMGUI_SFML_VERSION 2.5)
set(IMGUI_VERSION 1.86)
set(GOOGLETEST_VERSION 1.12.1)
set(BOX2D_VERSION 2.4.1)

cmake_policy(SET CMP0135 NEW)

FetchContent_Declare(
  SFML
  URL https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip
)

FetchContent_Declare(
  imgui-sfml
  URL https://github.com/SFML/imgui-sfml/archive/v${IMGUI_SFML_VERSION}.zip
)

FetchContent_Declare(
  imgui
  URL https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-${GOOGLETEST_VERSION}.zip
)

IF(WIN32)
  FetchContent_Declare(
    box2d
    URL https://github.com/erincatto/box2d/archive/v${BOX2D_VERSION}.zip
  )
  message(STATUS "Fetching Box2D...")
  option(BOX2D_BUILD_DOCS OFF)
  FetchContent_MakeAvailable(box2d)
ENDIF()

message(STATUS "Fetching SFML...")

# No need to build audio and network modules
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
option(SFML_BUILD_SYSTEM "Build system" OFF)
option(SFML_BUILD_EXAMPLES "Build examples" OFF)
FetchContent_MakeAvailable(SFML)

message(STATUS "Fetching ImGui...")
FetchContent_MakeAvailable(imgui)

message(STATUS "Fetching ImGui-SFML...")
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)
FetchContent_MakeAvailable(imgui-sfml)

message(STATUS "Fetching GoogleTest...")
FetchContent_MakeAvailable(googletest)
