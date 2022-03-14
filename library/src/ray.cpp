#include "library/include/ray.hpp"

Ray::Ray() : mOrigin(), mDirection(), mDistance(0.0f) {
}

Ray::Ray(const Vector &origin, const Vector &direction, const float distance) : mOrigin(origin), mDirection(direction), mDistance(distance) {
}

const Vector &Ray::origin() const {
    return mOrigin;
}

const Vector &Ray::direction() const {
    return mDirection;
}

float Ray::distance() const {
    return mDistance;
}

void Ray::setOrigin(const Vector& origin) {
    mOrigin = origin;
}

void Ray::setDirection(const Vector& direction) {
    mDirection = direction;
}

void Ray::setDistance(float distance) {
    mDistance = distance;
}


