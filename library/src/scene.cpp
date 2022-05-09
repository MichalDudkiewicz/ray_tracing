#include "scene.hpp"

Scene::Scene() : mCamera(*this) {
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

void Scene::addLight(const std::shared_ptr<Light> &light) {
    mLight.push_back(light);
}

const std::vector<std::shared_ptr<Light>> &Scene::light() const {
    return mLight;
}
