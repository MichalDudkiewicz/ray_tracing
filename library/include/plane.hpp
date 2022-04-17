#pragma once

#include "surface.hpp"
#include "vector.hpp"

class Plane : public Surface {
public:
    Plane(const Vector& lowerLeftCorner, const Vector& upperRightCorner, const Vector& normal);

    std::optional<Vector> intersection(const Ray& ray) const override;

    const Vector& upperRightCorner() const;
    const Vector& lowerLeftCorner() const;

private:
    Vector mLowerLeftCorner;
    Vector mUpperRightCorner;
};

