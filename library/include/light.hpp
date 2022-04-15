#pragma once

#include "vector.hpp"
#include "light_intensity.hpp"
#include "intersection_info.hpp"
#include "ray.hpp"

class Light {
public:
    explicit Light(const LightIntensity& lightIntensity);

public:
    LightIntensity diffuse(const IntersectionInfo& iInfo) const;

    LightIntensity specular(const IntersectionInfo& iInfo, const Ray& ray) const;

public:
    virtual Vector lightDirection(const Vector& position) const = 0;

private:
    virtual LightIntensity lightIntensity(const Vector& position) const = 0;

protected:
    LightIntensity mLightIntensity;
};
