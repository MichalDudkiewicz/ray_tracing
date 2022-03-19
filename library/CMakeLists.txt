project(ray_tracing_library)

add_library(library STATIC
        src/vector.cpp
        src/vector_operators.cpp
        src/ray.cpp
        src/sphere.cpp
        src/surface.cpp
        src/light_intensity.cpp
        )

target_include_directories(library PUBLIC include)
