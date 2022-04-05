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
        float i2 = (b + det) / a;
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
        if (intersections[0].z() > intersections[1].z())
        {
            intersectionPointOpt = intersections[0];
        }
        else
        {
            intersectionPointOpt = intersections[1];
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

void Sphere::setColor(const LightIntensity &color) {
    const auto red = (int)(color.red() * 255);
    const auto green = (int)(color.green() * 255);
    const auto blue = (int)(color.blue() * 255);

    mColor.Red = red;
    mColor.Green = green;
    mColor.Blue = blue;
}

RGBApixel Sphere::color() const {
    return mColor;
}
