#pragma once

#include "camera.hpp"
#include "ray.hpp"

class OrthographicCamera : public Camera {
public:
    OrthographicCamera(Scene& scene);
    OrthographicCamera(Scene& scene, const Vector &position, const Vector &target);

private:
    Ray createRay(float pixelX, float pixelY) const;
};

