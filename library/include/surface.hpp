#pragma once

#include "vector.hpp"
#include "ray.hpp"

#include <optional>

class Surface {
public:
    Surface(const Vector& point, const Vector& normal);

    const Vector& point();
    const Vector& normal();

    float shift() const;

    std::optional<Vector> intersectionPoint(const Ray& ray) const;

private:
    Vector mPoint;
    Vector mNormal;
};

