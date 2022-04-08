#pragma once

#include "vector.hpp"
#include "light_intensity.hpp"
#include "intersection_info.hpp"

class Light {
public:
    Light(const LightIntensity& lightIntensity);

public:
    LightIntensity diffuse(const IntersectionInfo& iInfo) const;

//    LightIntensity specular(const IntersectionInfo& iInfo, const Vector& cameraPosition) const;

private:
    virtual Vector lightDirection(const Vector& position) const = 0;
    virtual LightIntensity lightIntensity(const Vector& position) const = 0;

protected:
    LightIntensity mLightIntensity;
};
