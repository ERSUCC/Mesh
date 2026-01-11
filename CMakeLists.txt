cmake_minimum_required(VERSION 3.21)

project(mesh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# build library

add_library(mesh SHARED src/mesh.cpp)

target_include_directories(mesh PRIVATE include)

# build test suite

add_executable(mesh_tests test/src/lodepng.cpp
                          test/src/main.cpp)

target_include_directories(mesh_tests PRIVATE include test/include)
target_link_libraries(mesh_tests mesh)
