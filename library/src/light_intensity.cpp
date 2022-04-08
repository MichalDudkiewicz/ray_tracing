#include <algorithm>
#include "light_intensity.hpp"

LightIntensity::LightIntensity(float r, float g, float b) : mR(r), mG(g), mB(b) {
    mR = std::clamp(mR, 0.0f, 1.0f);
    mG = std::clamp(mG, 0.0f, 1.0f);
    mB = std::clamp(mB, 0.0f, 1.0f);
}

float LightIntensity::red() const {
    return mR;
}

float LightIntensity::green() const {
    return mG;
}

float LightIntensity::blue() const {
    return mB;
}

void LightIntensity::operator()(float r, float g, float b) {
    mR = r;
    mG = g;
    mB = b;
    mR = std::clamp(mR, 0.0f, 1.0f);
    mG = std::clamp(mG, 0.0f, 1.0f);
    mB = std::clamp(mB, 0.0f, 1.0f);
}

void LightIntensity::add(float r, float g, float b) {
    mR += r;
    mG += g;
    mB += b;
    mR = std::clamp(mR, 0.0f, 1.0f);
    mG = std::clamp(mG, 0.0f, 1.0f);
    mB = std::clamp(mB, 0.0f, 1.0f);
}

LightIntensity LightIntensity::operator+(const LightIntensity &li) const {
    return {mR + li.mR, mG + li.mG, mB + li.mB};
}

LightIntensity LightIntensity::operator-(const LightIntensity &li) const {
    return {mR - li.mR, mG - li.mG, mB - li.mB};
}

LightIntensity LightIntensity::operator/(float num) const {
    if (num == 0.0f)
    {
        return {0.0f, 0.0f, 0.0f};
    }
    return {mR / num, mG / num, mB / num};
}

LightIntensity LightIntensity::operator*(float num) const {
    return {mR * num, mG * num, mB * num};
}

LightIntensity operator*(float num, LightIntensity &li) {
    return {li.mR * num, li.mG * num, li.mB * num};
}

std::ostream& operator<<(std::ostream &str, const LightIntensity &li) {
    str << "LightIntensity[" << li.mR << ',' << li.mG << ',' << li.mB << ']';
    return str;
}

LightIntensity& LightIntensity::operator-=(const LightIntensity &li) {
    *this = *this - li;
    return *this;
}

LightIntensity& LightIntensity::operator+=(const LightIntensity &li) {
    *this = *this + li;
    return *this;
}

LightIntensity &LightIntensity::operator*=(float num) {
    *this = *this * num;
    return *this;
}

LightIntensity &LightIntensity::operator/=(float num) {
    *this = *this / num;
    return *this;
}

RGBApixel LightIntensity::toColor() const {
    const auto red = (int)(mR * 255);
    const auto green = (int)(mG * 255);
    const auto blue = (int)(mB * 255);

    RGBApixel color;
    color.Red = red;
    color.Green = green;
    color.Blue = blue;
    color.Alpha = 255;
    return color;
}
