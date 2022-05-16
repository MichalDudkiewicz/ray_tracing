#pragma once

#include "ray.hpp"
#include "vector.hpp"
#include "light_intensity.hpp"
#include "material.hpp"
#include "cuboid.hpp"
#include <optional>
#include <memory>

class Primitive {
public:
    Primitive(const Vector& lowerCorner, const Vector& upperCorner);

    Primitive() = default;

    virtual std::optional<Vector> intersection(const Ray &ray) const = 0;

    virtual Vector normal(const Vector& intersectionPoint) const = 0;

    friend class Mesh;

protected:
    std::optional<Cuboid> mBoundingBox;
};

