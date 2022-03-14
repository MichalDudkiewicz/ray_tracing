#pragma once

#include "vector.hpp"
#include "ray.hpp"
#include <vector>

class Sphere {
public:
    Sphere(const Vector& center, float radius = 0.0f);

    const Vector& center() const;
    float radius() const;

    bool isOnSurface(const Vector& point) const;
    std::vector<Vector> intersect(const Ray& ray) const;

private:
    Vector mCenter;
    float mRadius;
};
