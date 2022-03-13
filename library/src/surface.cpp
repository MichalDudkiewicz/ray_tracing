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

const Vector &Surface::normal() {
    return mNormal;
}

std::optional<Vector> Surface::intersectionPoint(const Ray &ray) const {
    const auto t = shift();
    const auto nDotV = mNormal.dotProduct(ray.direction());
    // ray is parallel to surface or ray intersects surface before its start point
    if (nDotV == 0.0f || ((t - mNormal.dotProduct(ray.origin())) / nDotV) < 0.0f)
    {
        return std::nullopt;
    }

    const auto w = ray.origin() - ray.direction();
    float wX = w.x();
    float wY = w.y();
    float wZ = w.z();
    float sqr = sqrtf((wX*wX) + (wY*wY) + (wZ*wZ));
    wX /= sqr;
    wY /= sqr;
    wZ /= sqr;

    float dot1 = (ray.origin().x()*mNormal.x() + ray.origin().y()*mNormal.y() + ray.origin().z()*mNormal.z()) - t;
    float dot2 = (wX*mNormal.x() + wY*mNormal.y() + wZ*mNormal.z());
    float ratio = dot1/dot2;
    float x_cross = ray.origin().x() - (wX * ratio);
    float y_cross = ray.origin().y() - (wY * ratio);
    float z_cross = ray.origin().z() - (wZ * ratio);
    return Vector{x_cross, y_cross, z_cross};
}
