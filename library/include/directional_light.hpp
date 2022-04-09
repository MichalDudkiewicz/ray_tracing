#pragma once

#include "light.hpp"

class DirectionalLight : public Light {
public:
    DirectionalLight(const LightIntensity& lightIntensity, const Vector& direction, float shininess = 2.0f);

private:
    Vector lightDirection(const Vector &position) const override;
    LightIntensity lightIntensity(const Vector &position) const override;

private:
    Vector mDirection;
};
