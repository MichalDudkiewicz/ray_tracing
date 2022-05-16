#include "cuboid.hpp"
#include "surface.hpp"

Cuboid::Cuboid(const Vector& lowerCorner, const Vector& upperCorner)
: mLowerCorner(lowerCorner), mUpperCorner(upperCorner)
{
}

Vector &Cuboid::lowerCorner() {
    return mLowerCorner;
}

Vector &Cuboid::upperCorner() {
    return mUpperCorner;
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
bool Cuboid::intersects(const Ray &ray) const {
    float tmin = (mLowerCorner.x() - ray.origin().x()) / ray.direction().x();
    float tmax = (mUpperCorner.x() - ray.origin().x()) / ray.direction().x();

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (mLowerCorner.y() - ray.origin().y()) / ray.direction().y();
    float tymax = (mUpperCorner.y() - ray.origin().y()) / ray.direction().y();

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (mLowerCorner.z() - ray.origin().z()) / ray.direction().z();
    float tzmax = (mUpperCorner.z() - ray.origin().z()) / ray.direction().z();

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return true;
}
