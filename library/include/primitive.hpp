#pragma once

#include "ray.hpp"
#include "vector.hpp"
#include "light_intensity.hpp"
#include "material.hpp"
#include <optional>
#include <memory>

class Primitive {
public:
    virtual std::optional<Vector> intersection(const Ray &ray) const = 0;

    virtual Vector normal(const Vector& intersectionPoint) const = 0;
};

