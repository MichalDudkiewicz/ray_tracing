#pragma once

#include "ray.hpp"
#include "vector.hpp"
#include "light_intensity.hpp"
#include <optional>

class Primitive {
public:
    virtual std::optional<Vector> intersection(const Ray &ray) const = 0;

    void setAmbientLightIntensity(const LightIntensity& ambientLightIntensity);
    const LightIntensity& ambientLightIntensity() const;

private:
    LightIntensity mAmbientLightIntensity;
};

