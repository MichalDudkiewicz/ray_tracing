#include "point_light.hpp"

Vector PointLight::lightDirection(const Vector &position) const {
    return mPosition - position;
}

PointLight::PointLight(const LightIntensity &lightIntensity, const Vector &position)
: Light(lightIntensity), mPosition(position)
{

}
