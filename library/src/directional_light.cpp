#include "directional_light.hpp"

Vector DirectionalLight::lightDirection(const Vector&/*position*/) const {
    return mDirection * (-1);
}
DirectionalLight::DirectionalLight(const LightIntensity &lightIntensity, const Vector &direction)
: Light(lightIntensity), mDirection(direction)
{

}

LightIntensity DirectionalLight::lightIntensity(const Vector &/*position*/) const {
    return mLightIntensity;
}
