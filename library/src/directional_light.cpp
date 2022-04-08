#include "directional_light.hpp"

Vector DirectionalLight::lightDirection(const Vector &/*position*/) const {
    return mDirection;
}

DirectionalLight::DirectionalLight(const LightIntensity &lightIntensity, const Vector &direction)
: Light(lightIntensity), mDirection(direction)
{

}
