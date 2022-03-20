#include "orthographic_camera.hpp"

OrthographicCamera::OrthographicCamera(Scene &scene) : Camera(scene) {

}

OrthographicCamera::OrthographicCamera(Scene &scene, const Vector &position, const Vector &target) : Camera(scene,
                                                                                                            position,
                                                                                                            target) {

}

Ray OrthographicCamera::createRay(float pixelX, float pixelY) const {
    return {{pixelX, pixelY, 0}, {0, 0, -1.0}, mFarPlane};
}
