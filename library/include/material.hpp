#pragma once
#include "light_intensity.hpp"

class Material {
public:
    Material(const LightIntensity& lightIntensity = {}, float diffuseCoeff = 0.0f, float specularCoeff = 0.0f);

    const LightIntensity& lightIntensity() const;

    float diffuseCoeff() const;

    float specularCoeff() const;

private:
    LightIntensity mLightIntensity;
    float mDiffuseCoeff;
    float mSpecularCoeff;
};

