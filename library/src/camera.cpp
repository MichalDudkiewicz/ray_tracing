#define _USE_MATH_DEFINES

#include "camera.hpp"
#include "scene.hpp"
#include "vector_operators.hpp"
#include "EasyBMP_BMP.h"
#include <cmath>

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

    RGBApixel backgroundColor;
    backgroundColor.Red = 180;
    backgroundColor.Blue = 180;
    backgroundColor.Green = 180;
    backgroundColor.Alpha = 255;

    

    for (int i = 0; i < image.TellWidth(); i++)
    {

        for (int j = 0; j < image.TellHeight(); j++)
        {
            image.SetPixel(i, j, backgroundColor);

        }

    }

    for (int i = 0; i < image.TellWidth(); i++)
    {
        const float x = float(i + 0.5) / float(image.TellWidth());
        for (int j = 0; j < image.TellHeight(); j++)
        {
            const float y = 1.0f - float(j + 0.5) / float(image.TellHeight());
            const Vector pixelPoint(c + x*a + y*b);
            const Ray ray = createRay(pixelPoint.x(), pixelPoint.y());

            float minZIntersection = -mFarPlane;
            for (const auto& primitive : mScene.primitives())
            {
                const auto intersection = primitive.intersect(ray);
                if (!intersection.empty())
                {
                    const auto& minZIntersectionPoint = intersection.front();
                    if (minZIntersectionPoint.z() > minZIntersection)
                    {
                        image.SetPixel(i, j, primitive.color());
                        minZIntersection = minZIntersectionPoint.z();
                    }
                    if (intersection.size() > 1)
                    {
                        for (int k = 1; k < intersection.size(); k++)
                        {
                            if (intersection[k].z() > minZIntersection)
                            {
                                image.SetPixel(i, j, primitive.color());
                                minZIntersection = intersection[k].z();
                            }
                        }
                    }
                }
            }
        }
    }
    return image;
}
