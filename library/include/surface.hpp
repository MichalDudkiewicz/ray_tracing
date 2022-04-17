#pragma once

#include "vector.hpp"
#include "ray.hpp"
#include "primitive.hpp"

#include <optional>

class Surface : public Primitive {
public:
    Surface(const Vector& point, const Vector& normal);

    const Vector& point();
    Vector normal(const Vector& intersectionPoint) const override;

    float shift() const;

    std::optional<Vector> intersection(const Ray& ray) const override;

private:
    Vector mPoint;
    Vector mNormal;
};

