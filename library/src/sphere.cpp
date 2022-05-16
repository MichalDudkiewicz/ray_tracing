#include "sphere.hpp"
#include <cmath>
#include <vector>
#include "vector_operators.hpp"

Sphere::Sphere(const Vector &center, float radius)
: Primitive({center.x()-radius, center.y()-radius, center.z()-radius}, {center.x()+radius, center.y()+radius, center.z()+radius}),
  mCenter(center), mRadius(radius)
{
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

float roundTo3(float var)
{
    int value = (int)(var * 1000 + .5);
    return (float)value / 1000;
}

std::optional<Vector> Sphere::intersection(const Ray &ray) const {
    const float dist = ray.distance();
    Vector v = ray.origin() - mCenter;
    const float b = - ray.direction().dotProduct(v);
    const float a = ray.direction().dotProduct(ray.direction());
    const float delta = ray.direction().dotProduct(v)*ray.direction().dotProduct(v)
            - ray.direction().dotProduct(ray.direction()) * (v.dotProduct(v) - powf(mRadius, 2.0f));
    std::optional<Vector> intersectionPointOpt;
    if (delta > 0) {
        const auto det = sqrtf(delta);
        float i1 = (b - det) / a;
        i1 = roundTo3(i1);
        float i2 = (b + det) / a;
        i2 = roundTo3(i2);
        std::vector<Vector> intersections;
        if (i2 >= 0 && i2 <= dist)
        {
            Vector intersectionPoint = ray.origin() + i2 * ray.direction();
            intersections.push_back(intersectionPoint);
        }
        if (i1 >= 0 && i1 <= dist)
        {
            Vector intersectionPoint = ray.origin() + i1 * ray.direction();
            intersections.push_back(intersectionPoint);
        }
        if (intersections.size() == 2)
        {
            if (intersections[0].z() > intersections[1].z())
            {
                intersectionPointOpt = intersections[0];
            }
            else
            {
                intersectionPointOpt = intersections[1];
            }
        }
        else if (intersections.size() == 1)
        {
            intersectionPointOpt = intersections.front();
        }
    }
    else if (delta == 0)
    {
        float i1 = b / a;
        if (i1 >= 0 && i1 <= dist)
        {
            Vector intersectionPoint = ray.origin() + i1 * ray.direction();
            intersectionPointOpt = intersectionPoint;
        }
    }
    return intersectionPointOpt;
}

Vector Sphere::normal(const Vector& intersectionPoint) const {
    return (intersectionPoint - mCenter).normalize();
}
