#pragma once

#include "vector.hpp"
#include "ray.hpp"

enum IntersectionCase {
    MISS, HIT, INPRIM
};

class Sphere {
public:
    Sphere(const Vector& center, float radius = 0.0f);

    const Vector& center() const;
    float radius() const;

    bool isOnSurface(const Vector& point) const;
    IntersectionCase intersect(const Ray& ray, float& dist) const;

private:
    Vector mCenter;
    float mRadius;
};
