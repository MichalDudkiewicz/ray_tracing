#pragma once

#include "light.hpp"

class PointLight : public Light {
public:
    PointLight(const LightIntensity& lightIntensity, const Vector& position, float a1 = 0.5f, float a2 = 0.5f);

public:
    Vector lightDirection(const Vector &position) const override;

private:
    LightIntensity lightIntensity(const Vector &position) const override;

private:
    Vector mPosition;
    float mA1;
    float mA2;
};
