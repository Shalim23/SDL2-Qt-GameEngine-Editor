include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

set(CMAKE_FOLDER "SDL")

set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/_deps")
FetchContent_Declare(
    SDL2 
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.9
)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
FetchContent_MakeAvailable(SDL2)

set(CMAKE_FOLDER "")