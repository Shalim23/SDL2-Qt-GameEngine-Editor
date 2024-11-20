cmake_minimum_required(VERSION 3.30)

project(SDL2-Qt-GameEngine-Editor)

file(GLOB_RECURSE src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME} STATIC ${src_files})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${PROJECT_NAME} PROPERTIES EDITOR_POSTFIX "_ed")

target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Editor>:EDITOR=1>)

include(FetchContent)

set(CMAKE_FOLDER "SDL")

FetchContent_Declare(SDL2 URL https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-2.30.9.tar.gz)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
FetchContent_MakeAvailable(SDL2)

set(CMAKE_FOLDER "")

target_link_libraries(${PROJECT_NAME} SDL2::SDL2-static)

target_include_directories(${PROJECT_NAME}
    SYSTEM PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Public/Engine"
        $<$<CONFIG:Editor>:${CMAKE_CURRENT_SOURCE_DIR}/Public/Editor>)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src_files})
