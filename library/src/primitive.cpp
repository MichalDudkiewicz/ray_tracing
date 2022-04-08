#include "primitive.hpp"


void Primitive::setAmbientLightIntensity(const LightIntensity &ambientLightIntensity) {
    mAmbientLightIntensity = ambientLightIntensity;
}

const LightIntensity& Primitive::ambientLightIntensity() const {
    return mAmbientLightIntensity;
}
