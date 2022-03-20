#include <vector>
#include "camera.hpp"
#include "sphere.hpp"
#include "orthographic_camera.hpp"
#include "panoramic_camera.hpp"
#include <memory>

class Scene {
public:
    Scene();

    Camera& camera();

    void addPrimitive(const Sphere& sphere);

    const std::vector<Sphere>& primitives() const;

private:
    PanoramicCamera mCamera;
    std::vector<Sphere> mPrimitives;
};

