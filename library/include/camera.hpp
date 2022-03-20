#pragma once

#include "vector.hpp"

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

    void render() const;

private:
    Scene& mScene;
    Vector mPosition;
    Vector mTarget;
    Vector mUp;
    float mNearPlane;
    float mFarPlane;
    float mFov;
};
