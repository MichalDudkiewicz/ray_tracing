#include "primitive.hpp"


void Primitive::setColor(const LightIntensity &color) {
    const auto red = (int)(color.red() * 255);
    const auto green = (int)(color.green() * 255);
    const auto blue = (int)(color.blue() * 255);

    mColor.Red = red;
    mColor.Green = green;
    mColor.Blue = blue;
}

RGBApixel Primitive::color() const {
    return mColor;
}

Primitive::Primitive()
{
    mColor.Alpha = 255;
    mColor.Red = 0;
    mColor.Green = 0;
    mColor.Blue = 0;
}
