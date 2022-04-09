#pragma once

#include "vector.hpp"
#include "light_intensity.hpp"
#include "intersection_info.hpp"
#include "ray.hpp"

class Light {
public:
    Light(const LightIntensity& lightIntensity, float flashCoefficient = 2.0f);

public:
    LightIntensity diffuse(const IntersectionInfo& iInfo) const;

    LightIntensity specular(const IntersectionInfo& iInfo, const Ray& ray) const;

private:
    virtual Vector lightDirection(const Vector& position) const = 0;
    virtual LightIntensity lightIntensity(const Vector& position) const = 0;

protected:
    LightIntensity mLightIntensity;
    float mFlashCoefficient;
};
