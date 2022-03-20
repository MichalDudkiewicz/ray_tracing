#include "scene.hpp"

Scene::Scene() : mImage(), mCamera(*this), mPrimitives() {
    constexpr unsigned int kImageWidth = 800;
    constexpr unsigned int kImageHeight = 800;
    constexpr unsigned int kBitDepth = 32;
    mImage.SetSize(kImageWidth, kImageHeight);
    mImage.SetBitDepth(kBitDepth);
}

const Camera &Scene::camera() const {
    return mCamera;
}

void Scene::addPrimitive(const Sphere &sphere) {
    mPrimitives.push_back(sphere);
}

void Scene::saveImage() {
    mImage.WriteToFile("rendered_scene.bmp");
}

BMP &Scene::image() {
    return mImage;
}

const std::vector<Sphere> &Scene::primitives() const {
    return mPrimitives;
}
