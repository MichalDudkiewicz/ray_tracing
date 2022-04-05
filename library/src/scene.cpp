#include "scene.hpp"

Scene::Scene() : mCamera(*this), mPrimitives() {
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
