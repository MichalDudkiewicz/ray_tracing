#include "plane.hpp"
#include "vector_operators.hpp"

Plane::Plane(const Vector &lowerLeftCorner, const Vector &upperRightCorner, const Vector &normal)
: Surface((lowerLeftCorner + upperRightCorner) / 2, normal), mLowerLeftCorner(lowerLeftCorner), mUpperRightCorner(upperRightCorner)
{
}

std::optional<Vector> Plane::intersection(const Ray &ray) const {
    auto surfaceIntersection = Surface::intersection(ray);
    if (surfaceIntersection.has_value())
    {
        const Vector localLowerLeftCorner = mLowerLeftCorner - surfaceIntersection.value();
        const Vector localUpperLeftCorner = mUpperRightCorner - surfaceIntersection.value();
        // TODO: how to create plane properly?
        // angle between is more or equal to 90 degrees
        if (localUpperLeftCorner.dotProduct(localLowerLeftCorner) <= 0.0f)
        {
            return surfaceIntersection;
        }
    }
    return std::nullopt;
}

const Vector &Plane::upperRightCorner() const {
    return mUpperRightCorner;
}

const Vector &Plane::lowerLeftCorner() const {
    return mLowerLeftCorner;
}
