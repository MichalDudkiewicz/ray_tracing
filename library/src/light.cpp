#include "light.hpp"
#include <cmath>

LightIntensity Light::diffuse(const IntersectionInfo &iInfo) const {
    auto lightVector = lightDirection(iInfo.position);
    lightVector.normalize();
    const float shade = std::max(0.0f, lightVector.dotProduct(iInfo.normalVector));
    return lightIntensity(iInfo.position) * shade * iInfo.diffuseCoeff;
}

//LightIntensity Light::specular(const IntersectionInfo& iInfo, const Vector& cameraPosition) const
//{
//
//}

Light::Light(const LightIntensity& lightIntensity)
: mLightIntensity(lightIntensity)
{

}
