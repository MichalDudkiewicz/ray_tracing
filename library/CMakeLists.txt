project(library)

add_library(library STATIC
        src/vector.cpp
        src/vector_operators.cpp
        src/ray.cpp
        src/sphere.cpp
        src/surface.cpp
        src/light_intensity.cpp
        src/camera.cpp
        src/scene.cpp
        src/orthographic_camera.cpp
        src/panoramic_camera.cpp
        src/triangle.cpp
        src/mesh.cpp
        src/obj_parser.cpp
        src/light.cpp
        src/point_light.cpp
        src/directional_light.cpp
        src/intersection_info.cpp
        src/material.cpp
        src/mtl_parser.cpp
        src/texture.cpp
        src/plane.cpp
        src/primitive.cpp
        src/cuboid.cpp
        )

target_include_directories(library PUBLIC include EasyBMP_1.06)

add_subdirectory(EasyBMP_1.06)
target_link_libraries(library PUBLIC EasyBMP)

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    target_link_libraries(library PRIVATE OpenMP::OpenMP_CXX)
endif()