cmake_minimum_required(VERSION 3.17)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-O3 -Ofast")

if (GLOBAL_ILLUMINATION)
    add_definitions(-DGLOBAL_ILLUMINATION=1)
endif (GLOBAL_ILLUMINATION)

add_executable(ray_tracing main.cpp)

add_subdirectory(library)

target_link_libraries(ray_tracing PUBLIC library)
