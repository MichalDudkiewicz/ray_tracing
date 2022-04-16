#pragma once
#include "EasyBMP_BMP.h"
#include <vector>
#include "light_intensity.hpp"

class Texture {
public:
    explicit Texture(const BMP& bmp);

    const LightIntensity& color(float u, float v) const;

private:
    int mWidth;
    int mHeight;
    std::vector<std::vector<LightIntensity>> mColorMap;
};
