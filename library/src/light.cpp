#include "light.hpp"
#include <cmath>
#include "vector_operators.hpp"

LightIntensity Light::diffuse(const IntersectionInfo &iInfo) const {
    const auto lightVector = lightDirection(iInfo.position()).normalize();
    if (lightVector.dotProduct(iInfo.normal()) < 0)
    {
        return {0, 0, 0};
    }
    const float shade = std::max(0.0f, lightVector.dotProduct(iInfo.normal()));
    return lightIntensity(iInfo.position()) * shade * iInfo.material().diffuseLight();
}

LightIntensity Light::specular(const IntersectionInfo& iInfo, const Ray& ray) const
{
    const Vector V = ray.direction().normalize();
    const Vector& N = iInfo.normal();
    const Vector R = V - (N * N.dotProduct(V) * 2.0f);
    const float ss = powf(std::abs(R.dotProduct(V)), iInfo.material().shininess());
    return lightIntensity(iInfo.position()) * iInfo.material().specularLight() * ss;
}

Light::Light(const LightIntensity& lightIntensity)
: mLightIntensity(lightIntensity)
{

}
