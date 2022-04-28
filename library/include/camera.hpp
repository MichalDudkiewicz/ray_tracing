#pragma once

#include "vector.hpp"
#include "ray.hpp"
#include "EasyBMP_BMP.h"
#include "light_intensity.hpp"

class Scene;

class Camera {
public:
    Camera(Scene& scene);
    Camera(Scene& scene, const Vector& position, const Vector& target);

public:
    void setPosition(const Vector& newPosition);
    Vector position() const;
    void setTarget(const Vector& target);
    Vector target() const;
    void setUp(const Vector& up);
    Vector up() const;
    void setNearPlane(float nearPlane);
    float nearPlane() const;
    void setFarPlane(float farPlane);
    float farPlane() const;
    void setFov(float fov);
    float fov() const;

    BMP render() const;

protected:
    virtual Ray createRay(float pixelX, float pixelY) const = 0;

private:
    void dividePixel(const Vector& center, float width, float height, int& redSum, int& greenSum, int& blueSum, int& sum, int depth = 1) const;
    RGBApixel getColorByPosition(const Vector& position) const;
    LightIntensity traceRay(const Ray& ray, int reflectedRayCounter = 0) const;

protected:
    Scene& mScene;
    Vector mPosition;
    Vector mTarget;
    Vector mUp;
    float mNearPlane;
    float mFarPlane;
    float mFov;
};
