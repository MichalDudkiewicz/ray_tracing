#include "sphere.hpp"
#include <cmath>
#include <vector>
#include "vector_operators.hpp"

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

std::vector<Vector> Sphere::intersect(const Ray &ray) const {
    const float dist = ray.distance();
    Vector v = ray.origin() - mCenter;
//    float b = -v.dotProduct(ray.direction());
//    float det = (b * b) - v.dotProduct(v) + powf(mRadius, 2.0f);
    const float b = - ray.direction().dotProduct(v);
    const float a = ray.direction().dotProduct(ray.direction());
    const float delta = ray.direction().dotProduct(v)*ray.direction().dotProduct(v)
            - ray.direction().dotProduct(ray.direction()) * (v.dotProduct(v) - powf(mRadius, 2.0f));
    std::vector<Vector> intersectionPoints;
    if (delta > 0) {
        const auto det = sqrtf(delta);
        float i1 = (b - det) / a;
        float i2 = (b + det) / a;
        if (i2 >= 0 && i2 <= dist)
        {
            Vector intersectionPoint = ray.origin() + i2 * ray.direction();
            intersectionPoints.push_back(intersectionPoint);
        }
        if (i1 >= 0 && i1 <= dist)
        {
            Vector intersectionPoint = ray.origin() + i1 * ray.direction();
            intersectionPoints.push_back(intersectionPoint);
        }
    }
    else if (delta == 0)
    {
        float i1 = b / a;
        if (i1 >= 0 && i1 <= dist)
        {
            Vector intersectionPoint = ray.origin() + i1 * ray.direction();
            intersectionPoints.push_back(intersectionPoint);
        }
    }
    return intersectionPoints;
}
