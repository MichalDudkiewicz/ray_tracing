#include "scene.hpp"

Scene::Scene() : mCamera(*this), mPrimitives() {
}

Camera& Scene::camera() {
    return mCamera;
}

void Scene::addPrimitive(const Sphere &sphere) {
    mPrimitives.push_back(sphere);
}

const std::vector<Sphere> &Scene::primitives() const {
    return mPrimitives;
}
