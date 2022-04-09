#include "material.hpp"

const LightIntensity &Material::lightIntensity() const {
    return mLightIntensity;
}

float Material::diffuseCoeff() const {
    return mDiffuseCoeff;
}

float Material::specularCoeff() const {
    return mSpecularCoeff;
}

Material::Material(const LightIntensity &lightIntensity, float diffuseCoeff, float specularCoeff)
: mLightIntensity(lightIntensity), mDiffuseCoeff(diffuseCoeff), mSpecularCoeff(specularCoeff)
{

}
