#pragma once

#include "vector.hpp"
#include "primitive.hpp"
#include "ray.hpp"
#include <vector>

class Sphere : public Primitive {
public:
    Sphere(const Vector& center, float radius = 0.0f);

    const Vector& center() const;
    float radius() const;

    Vector normal(const Vector& intersectionPoint) const override;

    bool isOnSurface(const Vector& point) const;
    std::optional<Vector> intersection(const Ray& ray) const override;

private:
    Vector mCenter;
    float mRadius;
};
