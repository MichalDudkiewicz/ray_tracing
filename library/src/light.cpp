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
    return lightIntensity(iInfo.position()) * shade * iInfo.material().diffuseCoeff();
}

LightIntensity Light::specular(const IntersectionInfo& iInfo, const Ray& ray) const
{
    Vector V = ray.direction().normalize();
    V.negate();
    const Vector N = iInfo.normal();
    Vector L = lightDirection(iInfo.position()).normalize();
    if (L.dotProduct(N) < 0)
    {
        return {0, 0, 0};
    }
    const Vector R = V - (N * N.dotProduct(V) * 2.0f);
    const float ss = powf(std::abs(R.dotProduct(V)), 2.0f);
    return lightIntensity(iInfo.position()) * iInfo.material().specularCoeff() * ss;
}

Light::Light(const LightIntensity& lightIntensity, float flashCoefficient)
: mLightIntensity(lightIntensity), mFlashCoefficient(flashCoefficient)
{

}
