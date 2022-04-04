#pragma once

#include "ray.hpp"
#include "vector.hpp"

#include <optional>

class Primitive {
public:
    virtual std::optional<Vector> intersection(const Ray &ray) const = 0;
};

