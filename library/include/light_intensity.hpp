#pragma once

#include <ostream>
#include "EasyBMP_DataStructures.h"

class LightIntensity
{
public:
    LightIntensity(float r = 0.0, float g = 0.0, float b = 0.0);

    LightIntensity(const LightIntensity& lightIntensity) = default;

    float red() const;
    float green() const;
    float blue() const;

    void operator()(float r, float g = 0.0, float b = 0.0);

    void add(float r, float g, float b);

    LightIntensity operator+(const LightIntensity &li) const;
    LightIntensity operator-(const LightIntensity &li) const;
    LightIntensity operator/(float num) const;
    LightIntensity operator*(float num) const;
    LightIntensity& operator-=(const LightIntensity &li);
    LightIntensity& operator+=(const LightIntensity &li);
    LightIntensity& operator*=(float num);
    LightIntensity& operator/=(float num);

    friend LightIntensity operator*(float num, LightIntensity &li);
    friend std::ostream& operator<<(std::ostream& str,
                                    const LightIntensity &li);

    RGBApixel toColor() const;

private:
    float mR, mG, mB;
};