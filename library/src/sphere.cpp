#include "library/include/sphere.hpp"
#include <cmath>

Sphere::Sphere(const Vector &center, float radius) : mCenter(center), mRadius(radius) {
}

const Vector &Sphere::center() const {
    return mCenter;
}

float Sphere::radius() const {
    return mRadius;
}

bool Sphere::isOnSurface(const Vector &point) const {
    const auto pointOriginDiff = point - mCenter;
    return (pointOriginDiff.dotProduct(pointOriginDiff) - powf(mRadius, 2.0f)) == 0.0f;
}

IntersectionCase Sphere::intersect(const Ray &ray, float &dist) const {
    Vector v = ray.origin() - mCenter;
    float b = -v.dotProduct(ray.direction());
    float det = (b * b) - v.dotProduct(v) + powf(mRadius, 2.0f);
    IntersectionCase intersectionCase = MISS;
    if (det > 0) {
        det = sqrtf(det);
        float i1 = b - det;
        float i2 = b + det;
        if (i2 > 0) {
            if (i1 < 0) {
                if (i2 < dist) {
                    dist = i2;
                    intersectionCase = INPRIM;
                }
            } else {
                if (i1 < dist) {
                    dist = i1;
                    intersectionCase = HIT;
                }
            }
        }
    }
    return intersectionCase;
}
