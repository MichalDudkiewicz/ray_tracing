#pragma once

#include "vector.hpp"
#include "ray.hpp"
#include <optional>
#include "primitive.hpp"

class Triangle : public Primitive {
public:
    Triangle(const Vector& a, const Vector& b, const Vector& c, const Vector& normal);
    Triangle(const Vector& a, const Vector& b, const Vector& c);

    std::optional<Vector> intersection(const Ray& ray) const override;

    const Vector& normal() const;

private:
    bool isInsideTriangle(const Vector& point) const;

private:
    Vector mA;
    Vector mB;
    Vector mC;
    Vector mNormal;
};
