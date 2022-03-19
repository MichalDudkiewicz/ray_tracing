#include "camera.hpp"

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

Camera::Camera() : mPosition(0, 0, 0), mTarget(0, 0, 1), mNearPlane(1), mFarPlane(1000), mUp(0, 1, 0) {
}

Camera::Camera(const Vector &position, const Vector &target)
: mPosition(position),
  mTarget(target),
  mNearPlane(1),
  mFarPlane(1000),
  mUp(0, 1, 0) {

}
