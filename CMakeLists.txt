cmake_minimum_required(VERSION 3.17)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(ray_tracing main.cpp)

add_subdirectory(library)
