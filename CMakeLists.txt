cmake_minimum_required(VERSION 3.30)

project(SDL2-Qt-GameEngine-Editor)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

file(GLOB_RECURSE src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME} STATIC ${src_files})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${PROJECT_NAME} PROPERTIES EDITOR_POSTFIX "_ed")

target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Editor>:EDITOR=1>)

include(${CMAKE_CURRENT_SOURCE_DIR}/Private/SDL2.cmake)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2-static
    $<$<CONFIG:Editor>:Qt6::Widgets>)

target_include_directories(${PROJECT_NAME}
    SYSTEM PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Public/Engine"
        $<$<CONFIG:Editor>:${CMAKE_CURRENT_SOURCE_DIR}/Public/Editor>
        $<$<CONFIG:Editor>:${QT_PATH}/include>)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src_files})
