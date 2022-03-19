#pragma once

#include <ostream>

class LightIntensity
{
public:
    LightIntensity(float r = 0.0, float g = 0.0, float b = 0.0);

    float red() const;
    float green() const;
    float blue() const;

    void operator()(float r, float g = 0.0, float b = 0.0);

    void add(float r, float g, float b);

    LightIntensity operator+(const LightIntensity &li) const;
    LightIntensity operator-(const LightIntensity &li) const;
    LightIntensity operator/(float num) const;
    LightIntensity operator*(float num) const;

    friend LightIntensity operator*(float num, LightIntensity &li);
    friend std::ostream& operator<<(std::ostream& str,
                                    const LightIntensity &li);

private:
    float mR, mG, mB;
};