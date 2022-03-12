#include "ray.hpp"

Ray::Ray() : mOrigin(), mDirection(), mDistance(0.0f) {
}

Ray::Ray(const Vector &o, const Vector &d) : mOrigin(o), mDirection(d), mDistance(0.0f) {
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


