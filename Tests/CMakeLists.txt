cmake_minimum_required(VERSION 3.30)

project(SDL2-Qt-GameEngine-Editor-Tests)

file(GLOB_RECURSE src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(CMAKE_FOLDER "GTEST")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_FOLDER "")

enable_testing()

add_executable(${PROJECT_NAME} ${src_files})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2-Qt-GameEngine-Editor gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src_files})
