#include <vector>
#include "camera.hpp"
#include "sphere.hpp"
#include "EasyBMP_BMP.h"
#include "orthographic_camera.hpp"
#include "panoramic_camera.hpp"
#include <memory>

class Scene {
public:
    Scene();

    const Camera& camera() const;

    void addPrimitive(const Sphere& sphere);

    void saveImage();

    BMP& image();

    const std::vector<Sphere>& primitives() const;

private:
    BMP mImage;
    PanoramicCamera mCamera;
    std::vector<Sphere> mPrimitives;
};

