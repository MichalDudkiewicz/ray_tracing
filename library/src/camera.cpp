#define _USE_MATH_DEFINES

#include "camera.hpp"
#include "scene.hpp"
#include "vector_operators.hpp"
#include "EasyBMP_BMP.h"
#include <cmath>

namespace {
    RGBApixel kBackgroundColor{180, 180, 180, 255};
}

void Camera::setPosition(const Vector &newPosition) {
    mPosition = newPosition;
}

Vector Camera::position() const {
    return mPosition;
}

void Camera::setTarget(const Vector &target) {
    mTarget = target;
}

Vector Camera::target() const {
    return mTarget;
}

void Camera::setUp(const Vector &up) {
    mUp = up;
}

Vector Camera::up() const {
    return mUp;
}

void Camera::setNearPlane(float nearPlane) {
    mNearPlane = nearPlane;
}

float Camera::nearPlane() const {
    return mNearPlane;
}

void Camera::setFarPlane(float farPlane) {
    mFarPlane = farPlane;
}

float Camera::farPlane() const {
    return mFarPlane;
}

void Camera::setFov(float fov) {
    mFov = fov;
}

float Camera::fov() const {
    return mFov;
}

void Camera::dividePixel(const Vector& center, float width, float height, int& redSum, int& greenSum, int& blueSum, int& sum, int depth) const {
    constexpr int kMaxDepth = 4;

    std::vector<RGBApixel> colors;
    const Vector leftUpperCorner = center + Vector{-width/2, height/2};
    const RGBApixel leftUpperCornerColor = getColorByPosition(leftUpperCorner);
    colors.push_back(leftUpperCornerColor);

    const Vector rightUpperCorner = center + Vector{width/2, height/2};
    const RGBApixel rightUpperCornerColor = getColorByPosition(rightUpperCorner);
    colors.push_back(rightUpperCornerColor);

    const Vector leftDownCorner = center + Vector{-width/2, -height/2};
    const RGBApixel leftDownCornerColor = getColorByPosition(leftDownCorner);
    colors.push_back(leftDownCornerColor);

    const Vector rightDownCorner = center + Vector{width/2, -height/2};
    const RGBApixel rightDownCornerColor = getColorByPosition(rightDownCorner);
    colors.push_back(rightDownCornerColor);

    if (depth + 1 > kMaxDepth || (leftUpperCornerColor == rightUpperCornerColor && leftUpperCornerColor == leftDownCornerColor && leftUpperCornerColor == rightDownCornerColor))
    {
        int r = 0;
        int g = 0;
        int b = 0;
        for (const auto& color : colors)
        {
            r += color.Red;
            g += color.Green;
            b += color.Blue;
        }
        const int weight = kMaxDepth - depth + 1;
        redSum += weight * r / 4;
        greenSum += weight * g / 4;
        blueSum += weight * b / 4;
        sum += weight;
    }
    else
    {
        const Vector centerToLeftUpperCorner = center + Vector{-width/4, height/4};
        dividePixel(centerToLeftUpperCorner, width/2, height/2, redSum, greenSum, blueSum, sum, depth+1);
        const Vector centerToRightUpperCorner = center + Vector{width/4, height/4};
        dividePixel(centerToRightUpperCorner, width/2, height/2, redSum, greenSum, blueSum, sum, depth+1);
        const Vector centerToLeftDownCorner = center + Vector{-width/4, -height/4};
        dividePixel(centerToLeftDownCorner, width/2, height/2, redSum, greenSum, blueSum, sum, depth+1);
        const Vector centerToRightDownCorner = center + Vector{width/4, -height/4};
        dividePixel(centerToRightDownCorner, width/2, height/2, redSum, greenSum, blueSum, sum, depth+1);
    }
}

Camera::Camera(Scene& scene) : mScene(scene), mPosition(0, 0, 0), mTarget(0, 0, -1), mNearPlane(1), mFarPlane(1000), mUp(0, 1, 0), mFov(100.0f) {
}

Camera::Camera(Scene& scene, const Vector &position, const Vector &target)
: mScene(scene),
  mPosition(position),
  mTarget(target),
  mNearPlane(1),
  mFarPlane(1000),
  mUp(0, 1, 0),
  mFov(100.0f) {

}

BMP Camera::render() const {
    constexpr unsigned int kBitDepth = 32;
    BMP image;
    image.SetBitDepth(kBitDepth);
    constexpr int ny = 600;
    const int nx = (int)(ny * mNearPlane * tanf((mFov / 2.0f) * M_PI / 180.f));
    constexpr float screenProportion = 2.0f;
    image.SetSize(nx, (int)(nx/screenProportion));

    const Vector w = (-1.0f) * mTarget.normalize();
    const Vector u = mUp.crossProduct(w) / mUp.crossProduct(w).length();
    const Vector v = w.crossProduct(u);

    const Vector c = -screenProportion * u - 1.0f * v - mNearPlane * w;
    const Vector b(2.0f * v);
    const Vector a(2 * screenProportion * u);

    const float pixelWidth = screenProportion / nx;
    const float pixelHeight = screenProportion / ny;
    for (int i = 0; i < image.TellWidth(); i++)
    {
        const float x = float(i + 0.5) / float(image.TellWidth());
        for (int j = 0; j < image.TellHeight(); j++)
        {
            const float y = 1.0f - float(j + 0.5) / float(image.TellHeight());
            const Vector pixelPoint(c + x*a + y*b);

            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            int sum = 0;
            dividePixel(pixelPoint, pixelWidth, pixelHeight, redSum, greenSum, blueSum, sum);
            RGBApixel color;
            color.Red = redSum / sum;
            color.Green = greenSum / sum;
            color.Blue = blueSum / sum;
            color.Alpha = 255;
            image.SetPixel(i, j, color);
        }
    }
    return image;
}

RGBApixel Camera::getColorByPosition(const Vector& position) const {
    float minZIntersection = -mFarPlane;
    RGBApixel color = kBackgroundColor;
    const Ray ray = createRay(position.x(), position.y());
    for (const auto& primitive : mScene.primitives())
    {
        const auto intersection = primitive.intersect(ray);
        if (!intersection.empty())
        {
            const auto& minZIntersectionPoint = intersection.front();
            if (minZIntersectionPoint.z() > minZIntersection)
            {
                color = primitive.color();
                minZIntersection = minZIntersectionPoint.z();
            }
            if (intersection.size() > 1)
            {
                for (int k = 1; k < intersection.size(); k++)
                {
                    if (intersection[k].z() > minZIntersection)
                    {
                        color = primitive.color();
                        minZIntersection = intersection[k].z();
                    }
                }
            }
        }
    }
    return color;
}
