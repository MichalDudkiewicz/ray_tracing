#include "camera.hpp"
#include "scene.hpp"

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

Camera::Camera(Scene& scene) : mScene(scene), mPosition(0, 0, 0), mTarget(0, 0, 1), mNearPlane(1), mFarPlane(1000), mUp(0, 1, 0) {
}

Camera::Camera(Scene& scene, const Vector &position, const Vector &target)
: mScene(scene),
  mPosition(position),
  mTarget(target),
  mNearPlane(1),
  mFarPlane(1000),
  mUp(0, 1, 0) {

}

void Camera::render() const {
    auto& image = mScene.image();
    const float pixelWidth = 2.0f / image.TellWidth();
    const float pixelHeight = 2.0f / image.TellHeight();
    for (int i = 0; i < image.TellWidth(); i++)
    {
        const auto centerX = -1.0f + (i + 0.5f) * pixelWidth;
        for (int j = 0; j < image.TellHeight(); j++)
        {
            const auto centerY = 1.0f - (j + 0.5f) * pixelHeight;
            const Ray ray({centerX, centerY, 0}, {0, 0, 1.0}, 200.0f);

            float minZIntersection = mFarPlane;
            for (const auto& primitive : mScene.primitives())
            {
                const auto intersection = primitive.intersect(ray);
                if (!intersection.empty())
                {
                    const auto& minZIntersectionPoint = intersection.front();
                    if (minZIntersectionPoint.z() < minZIntersection)
                    {
                        image.SetPixel(i, j, primitive.color());
                        minZIntersection = minZIntersectionPoint.z();
                    }
                    if (intersection.size() > 1)
                    {
                        for (int k = 1; k < intersection.size(); k++)
                        {
                            if (intersection[k].z() < minZIntersection)
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
}
