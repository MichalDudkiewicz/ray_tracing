#pragma once

#include "camera.hpp"

class PanoramicCamera : public Camera {
public:
    PanoramicCamera(Scene& scene);
    PanoramicCamera(Scene& scene, const Vector& position, const Vector& target);

private:
    Ray createRay(float pixelX, float pixelY) const override;
};
