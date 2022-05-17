#define _USE_MATH_DEFINES

#include "camera.hpp"
#include "scene.hpp"
#include "vector_operators.hpp"
#include "EasyBMP_BMP.h"
#include <cmath>
#include "intersection_info.hpp"
#include "plane.hpp"

namespace {
    constexpr int kMaxReflectedRaysNumber = 5;
}

namespace {
    constexpr RGBApixel kBackgroundColor{180, 180, 180, 255};
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
        const int weight = pow(2, kMaxDepth - depth);
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

Camera::Camera(Scene& scene) : mScene(scene), mPosition(0, 0, 0), mTarget(0, 0, -0.001), mNearPlane(1), mFarPlane(1000), mUp(0, 1, 0), mFov(100.0f) {
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
    // TODO: how to maintain rectangular image aspect ratio and use canonical space (-1,1) x2
    constexpr float screenProportion = 1.0f;
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
    Ray ray = createRay(position.x(), position.y());
    ray.setDistance(mFarPlane);
    return traceRay(ray).toColor();
}

LightIntensity Camera::traceRay(const Ray& ray, int reflectedRayCounter) const
{
    LightIntensity accumulatedLightIntensity(0.5, 0.5, 0.5);
    if (reflectedRayCounter < kMaxReflectedRaysNumber) {
        float minDistance = ray.distance();
        for (const auto &mesh: mScene.meshes()) {
            if (mesh.hasBoundingBox() && !mesh.intersectsBoundingBox(ray)) {
                continue;
            }

            const auto intersection = mesh.intersection(ray);
            if (intersection.has_value()) {
                const auto intersectionPoint = std::get<0>(intersection.value());
                const float newDistance = (intersectionPoint - ray.origin()).length();
                if (newDistance > minDistance) {
                    continue;
                } else {
                    minDistance = newDistance;
                }

                const auto texture = mesh.material().texture();
                LightIntensity textureLightIntensity(1.0f, 1.0f, 1.0f);
                if (texture) {
                    const auto primitiveHit = std::get<2>(intersection.value());
                    //TODO: how to handle any mesh and unwrapping any geometry?
                    const auto sphere = std::dynamic_pointer_cast<Sphere>(primitiveHit);
                    const auto plane = std::dynamic_pointer_cast<Plane>(primitiveHit);
                    if (sphere) {
                        const auto localCoordsIntersection = intersectionPoint - sphere->center();
                        auto phi = atanf(localCoordsIntersection.x() / localCoordsIntersection.z());
                        if (phi < 0.0f) {
                            phi += 2 * M_PI;
                        }
                        // TODO: what if radius is bigger than 1.0f?
                        // http://raytracerchallenge.com/bonus/texture-mapping.html?fbclid=IwAR03ywQ6spI8EHgCBHqTEC04idLVRhSY7m_eAlEozc5tN8Ug8V2M6zxLH1Q
                        const auto theta = acosf(localCoordsIntersection.y());
                        const float u = phi / (2 * M_PI);
                        const float v = 1.0f - theta / M_PI;
                        textureLightIntensity = texture->color(u, v);
                    } else if (plane) {
                        // TODO: how to handle normalising plane process correctly?
                        auto localCoordsIntersection = intersectionPoint - plane->point();
                        if (plane->normal(intersectionPoint).x() != 1.0f) {
                            localCoordsIntersection.setX(localCoordsIntersection.x() / std::abs(
                                    (plane->lowerLeftCorner().x() - plane->upperRightCorner().x())));
                        }
                        if (plane->normal(intersectionPoint).y() != 1.0f) {
                            localCoordsIntersection.setY(localCoordsIntersection.y() / std::abs(
                                    (plane->lowerLeftCorner().y() - plane->upperRightCorner().y())));
                        }
                        if (plane->normal(intersectionPoint).z() != 1.0f) {
                            localCoordsIntersection.setZ(localCoordsIntersection.z() / std::abs(
                                    (plane->lowerLeftCorner().z() - plane->upperRightCorner().z())));
                        }

                        // TODO: how to handle rotated plane, so that y is 0 and z is not?
                        const float u = ((localCoordsIntersection.y()) + 1.0f) / 2.0f;
                        const float v = (localCoordsIntersection.x() + 1.0f) / 2.0f;

                        textureLightIntensity = texture->color(u, v);
                    }
                }
                const auto ambientLightIntensity = mesh.material().ambientLight() * textureLightIntensity;

                accumulatedLightIntensity = ambientLightIntensity;

                IntersectionInfo intersectionInfo(mesh.material(), intersectionPoint,
                                                  std::get<1>(intersection.value()));

                for (const auto &light: mScene.lights()) {
                    auto lightDir = light->lightDirection(intersectionInfo.position()).normalize();
                    const Vector beforeIntersectionPoint = intersectionInfo.position() + 0.1 * lightDir;
                    // TODO: shadowRay distance for directional light should be calculated dirrefently than based on light position.
                    //  most probably it should be big number, in theory close to infinity
                    const Ray shadowRay(beforeIntersectionPoint, lightDir,
                                        light->lightDirection(beforeIntersectionPoint).length() - 0.01f);
                    bool isInShadow = false;
                    for (const auto &mesh2: mScene.meshes()) {
                        for (const auto &primitive2: mesh2.primitives()) {
                            const auto intersection2 = primitive2->intersection(shadowRay);
                            if (intersection2.has_value()) {
                                isInShadow = true;
                                break;
                            }
                        }
                    }
                    if (!isInShadow || mesh.material().refractionFactor() > 1.0f || mesh.material().isMirror()) {
                        const auto diffuseLightIntensity = light->diffuse(intersectionInfo) * textureLightIntensity;
                        const auto specularLightIntensity = light->specular(intersectionInfo, ray);
                        accumulatedLightIntensity += diffuseLightIntensity + specularLightIntensity;

                        if (mesh.material().isMirror()) {
                            const Vector V = ray.direction().normalize();
                            const Vector &N = intersectionInfo.normal();
                            const Vector R = V - (N * N.dotProduct(V) * 2.0f);

                            const Vector beforeIntersectionVPoint = intersectionInfo.position() + 0.1 * N;
                            Ray reflectedRay(beforeIntersectionVPoint, R, 1000.0f);
                            const auto reflectedLightIntensity = traceRay(reflectedRay, reflectedRayCounter + 1);
                            accumulatedLightIntensity += reflectedLightIntensity;
                        } else if (mesh.material().refractionFactor() > 1.0f) {
                            const Vector d = ray.direction().normalize();
                            const Vector &n = intersectionInfo.normal();
                            const auto lambdaT = mesh.material().refractionFactor();
                            Vector t = (d - n * (d.dotProduct(n))) / lambdaT -
                                       n * sqrtf(1 - (1 - powf(d.dotProduct(n), 2.0f)) / powf(lambdaT, 2.0f));
                            t = t.normalize();
                            const Vector innerIntersection = intersectionPoint - 0.01 * n;
                            const Ray innerRay(innerIntersection, t, 1000.0f);
                            const auto innerSecondIntersection = mesh.intersection(innerRay);
                            if (innerSecondIntersection.has_value()) {
                                const Vector &d2 = t;
                                Vector n2 = std::get<1>(innerSecondIntersection.value());
                                n2.negate();
                                Vector t2 = lambdaT * (d2 - n2 * (d2.dotProduct(n2))) -
                                            n2 * sqrtf(1 - powf(lambdaT, 2.0f) * (1 - powf(d2.dotProduct(n2), 2.0f)));
                                t2 = t2.normalize();
                                const auto innerSecondIntersectionPoint =
                                        std::get<0>(innerSecondIntersection.value()) - 0.01 * n2;
                                const Ray refractedRay(innerSecondIntersectionPoint, t2, 1000.0f);
                                const auto refractedLightIntensity = traceRay(refractedRay, reflectedRayCounter + 1);
                                accumulatedLightIntensity += refractedLightIntensity;
                            }
                        }
                    } else {
                        accumulatedLightIntensity -= mesh.material().shadowLight();
                    }
                }
            }
        }
    }
    return accumulatedLightIntensity;
}
