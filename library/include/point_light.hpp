#pragma once

#include "light.hpp"

class PointLight : public Light {
public:
    PointLight(const LightIntensity& lightIntensity, const Vector& position, float a1 = 1.0f, float a2 = 0.0f);

public:
    Vector lightDirection(const Vector &position) const override;
    LightIntensity lightIntensity(const Vector &position) const override;

private:
    Vector mPosition;
    float mA1;
    float mA2;
};
