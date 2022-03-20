#pragma once

#include "vector.hpp"
#include "ray.hpp"
#include "light_intensity.hpp"
#include "EasyBMP_DataStructures.h"
#include <vector>

class Sphere {
public:
    Sphere(const Vector& center, float radius = 0.0f);

    const Vector& center() const;
    float radius() const;

    bool isOnSurface(const Vector& point) const;
    std::vector<Vector> intersect(const Ray& ray) const;

    void setColor(const LightIntensity& color);
    RGBApixel color() const;

private:
    Vector mCenter;
    float mRadius;
    RGBApixel mColor;
};
