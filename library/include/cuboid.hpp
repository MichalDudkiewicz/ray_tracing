#pragma once

#include "vector.hpp"
#include "ray.hpp"
#include <optional>

class Cuboid {
public:
    explicit Cuboid(const Vector& lowerCorner = {}, const Vector& upperCorner={});

    Vector& lowerCorner();
    Vector& upperCorner();

    bool intersects(const Ray &ray) const;

private:
    Vector mLowerCorner;
    Vector mUpperCorner;
};


