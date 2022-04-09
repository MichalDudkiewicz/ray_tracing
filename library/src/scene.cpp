#include "scene.hpp"

Scene::Scene() : mCamera(*this), mPrimitives(), mLight({1.0, 1.0, 1.0}, {1,0, 1}, 0.5f, 0.5f, 2.0f) {
}

Camera& Scene::camera() {
    return mCamera;
}

void Scene::addMesh(const Mesh &mesh) {
    mMeshes.push_back(mesh);
}

const std::vector<Mesh> &Scene::meshes() const {
    return mMeshes;
}

const Light &Scene::light() const {
    return mLight;
}
