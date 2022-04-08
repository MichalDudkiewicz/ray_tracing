#pragma once

#include "light.hpp"

class PointLight : public Light {
public:
    PointLight(const LightIntensity& lightIntensity, const Vector& position);

public:
    Vector lightDirection(const Vector &position) const override;

private:
    Vector mPosition;
};
