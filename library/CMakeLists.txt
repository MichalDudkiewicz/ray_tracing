project(ray_tracing_library)

add_library(library STATIC
        src/vector.cpp
        )

target_include_directories(library PUBLIC include)
