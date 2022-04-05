#pragma once

#include "ray.hpp"
#include "vector.hpp"
#include "EasyBMP_DataStructures.h"
#include "light_intensity.hpp"
#include <optional>

class Primitive {
public:
    Primitive();

public:
    virtual std::optional<Vector> intersection(const Ray &ray) const = 0;

    void setColor(const LightIntensity& color);
    RGBApixel color() const;

private:
    RGBApixel mColor;
};

