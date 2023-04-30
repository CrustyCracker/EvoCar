message(STATUS "Fetching SFML...")

# No need to build audio and network modules
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_SYSTEM FALSE)
set(SFML_BUILD_EXAMPLES FALSE)
FetchContent_MakeAvailable(sfml)
