#include "surface.hpp"

#include <cmath>

Surface::Surface(const Vector &point, const Vector &normal) : mPoint(point), mNormal(normal) {
}

float Surface::shift() const {
    return mNormal.dotProduct(mPoint);
}

const Vector &Surface::point() {
    return mPoint;
}

Vector Surface::normal(const Vector& /*intersectionPoint*/) const {
    return mNormal;
}

std::optional<Vector> Surface::intersection(const Ray &ray) const {
    const auto t = shift();
    Vector V = ray.direction().normalize();
    V.negate();
    const auto nDotV = mNormal.dotProduct(V);
    // ray is parallel to surface or ray intersects surface before its start point
    if (nDotV != 0) {
//        Vector p0l0 = ray.origin() - mPoint;
//        const auto a = p0l0.dotProduct(mNormal) / nDotV;
        const auto a = (t - mNormal.dotProduct(ray.origin())) / nDotV;
        if (a <= 0)
        {
            return ray.origin() + V * a;
        }
        else
        {
            return std::nullopt;
        }
    }
    else
    {
        return std::nullopt;
    }
}
