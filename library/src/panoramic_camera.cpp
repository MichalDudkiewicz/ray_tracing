#include "panoramic_camera.hpp"

PanoramicCamera::PanoramicCamera(Scene &scene) : Camera(scene) {

}

PanoramicCamera::PanoramicCamera(Scene &scene, const Vector &position, const Vector &target) : Camera(scene, position,
                                                                                                      target) {

}

Ray PanoramicCamera::createRay(float pixelX, float pixelY) const {
    return {mPosition, {pixelX, pixelY, -1.0}, mFarPlane};
}
