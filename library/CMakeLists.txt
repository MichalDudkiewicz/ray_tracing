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
        src/primitive.cpp
        src/triangle.cpp
        )

target_include_directories(library PUBLIC include EasyBMP_1.06)

add_subdirectory(EasyBMP_1.06)
target_link_libraries(library PUBLIC EasyBMP)