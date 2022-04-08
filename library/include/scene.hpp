#include <vector>
#include "camera.hpp"
#include "sphere.hpp"
#include "orthographic_camera.hpp"
#include "panoramic_camera.hpp"
#include "mesh.hpp"
#include "point_light.hpp"
#include <memory>

class Scene {
public:
    Scene();

    Camera& camera();

    void addPrimitive(const Sphere& sphere);

    void addMesh(const Mesh& mesh);

    const std::vector<Sphere>& primitives() const;

    const std::vector<Mesh>& meshes() const;

    const Light& light() const;

private:
    PanoramicCamera mCamera;
    std::vector<Sphere> mPrimitives;
    std::vector<Mesh> mMeshes;
    PointLight mLight;
};

