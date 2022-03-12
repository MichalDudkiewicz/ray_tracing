project(ray_tracing_library)

add_library(library STATIC
        src/vector.cpp
        src/scalar_vector_operators.cpp
        )

target_include_directories(library PUBLIC include)
