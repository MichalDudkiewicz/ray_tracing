#include "point_light.hpp"

Vector PointLight::lightDirection(const Vector &position) const {
    return mPosition - position;
}

PointLight::PointLight(const LightIntensity &lightIntensity, const Vector &position, float a1, float a2)
: Light(lightIntensity), mPosition(position), mA1(a1), mA2(a2)
{

}

LightIntensity PointLight::lightIntensity(const Vector &position) const {
    return mLightIntensity / (mA1 + mA2 * (position - mPosition).length());
}
