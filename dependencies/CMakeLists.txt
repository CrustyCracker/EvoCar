include(FetchContent)

set(SFML_VERSION 2.5.1)
set(IMGUI_SFML_VERSION 2.5)
set(IMGUI_VERSION 1.86)
set(IMPLOT_VERSION 0.14)
set(GOOGLETEST_VERSION 1.12.1)
set(BOX2D_VERSION 2.4.1)
set(JSON_VERSION 3.11.2)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.24")
  cmake_policy(SET CMP0135 NEW)
endif()

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
  implot
  URL https://github.com/epezent/implot/archive/v${IMPLOT_VERSION}.zip
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-${GOOGLETEST_VERSION}.zip
)

FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/archive/v${JSON_VERSION}.zip
)

message(STATUS "Fetching JSON...")
FetchContent_MakeAvailable(json)

IF(WIN32)
  FetchContent_Declare(
    box2d
    URL https://github.com/erincatto/box2d/archive/v${BOX2D_VERSION}.zip
  )
  message(STATUS "Fetching Box2D...")
  option(BOX2D_BUILD_UNIT_TESTS "Build the Box2D unit tests" OFF)
  option(BOX2D_BUILD_TESTBED "Build the Box2D testbed" OFF)
  option(BOX2D_BUILD_DOCS "Build the Box2D documentation" OFF)
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
set(IMGUI_SRC
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui.cpp
)
set(IMGUI_HEADERS
  ${imgui_SOURCE_DIR}/imconfig.h
  ${imgui_SOURCE_DIR}/imgui_internal.h
  ${imgui_SOURCE_DIR}/imgui.h
  ${imgui_SOURCE_DIR}/imstb_rectpack.h
  ${imgui_SOURCE_DIR}/imstb_textedit.h
  ${imgui_SOURCE_DIR}/imstb_truetype.h
)
add_library(imgui STATIC
  ${IMGUI_HEADERS}
  ${IMGUI_SRC}
)

message(STATUS "Fetching ImPlot...")
FetchContent_MakeAvailable(implot)
set(IMPLOT_SRC
  ${implot_SOURCE_DIR}/implot.cpp
  ${implot_SOURCE_DIR}/implot_items.cpp
  ${implot_SOURCE_DIR}/implot_demo.cpp
)
set(IMPLOT_HEADERS
  ${implot_SOURCE_DIR}/implot.h
  ${implot_SOURCE_DIR}/implot_internal.h
)
add_library(implot STATIC
  ${IMPLOT_HEADERS}
  ${IMPLOT_SRC}
)
target_include_directories(implot PRIVATE ${imgui_SOURCE_DIR})
target_include_directories(implot PUBLIC ${implot_SOURCE_DIR})

message(STATUS "Fetching ImGui-SFML...")
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)
FetchContent_MakeAvailable(imgui-sfml)

message(STATUS "Fetching GoogleTest...")
FetchContent_MakeAvailable(googletest)

set(imgui_SOURCE_DIR "${imgui_SOURCE_DIR}" CACHE INTERNAL "")
set(imgui-sfml_SOURCE_DIR "${imgui-sfml_SOURCE_DIR}" CACHE INTERNAL "")
set(implot_SOURCE_DIR "${implot_SOURCE_DIR}" CACHE INTERNAL "")
