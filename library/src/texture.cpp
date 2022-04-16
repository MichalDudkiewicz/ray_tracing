#include "texture.hpp"

Texture::Texture(const BMP &bmp) {
    mHeight = bmp.TellHeight();
    mWidth = bmp.TellWidth();
    mColorMap.reserve(bmp.TellWidth());
    for (int i = 0; i < bmp.TellWidth(); i++)
    {
        mColorMap.emplace_back();
        mColorMap[i].reserve(bmp.TellHeight());
        for (int j = 0; j < bmp.TellHeight(); j++)
        {
            mColorMap[i].emplace_back(bmp.GetPixel(i, j));
        }
    }
}

const LightIntensity &Texture::color(float u, float v) const {
    const int y = (mHeight - 1) * u;
    const int x = (mWidth - 1) * v;
    return mColorMap[x][y];
}
