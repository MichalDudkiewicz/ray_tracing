#pragma once

#include "light.hpp"

class DirectionalLight : public Light {
public:
    DirectionalLight(const LightIntensity& lightIntensity, const Vector& direction);

public:
    Vector lightDirection(const Vector &position) const override;

private:
    LightIntensity lightIntensity(const Vector &position) const override;

private:
    Vector mDirection;
};
