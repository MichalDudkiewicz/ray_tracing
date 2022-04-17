#include "material.hpp"

const LightIntensity &Material::ambientLight() const {
    return mAmbientLight;
}

const LightIntensity& Material::diffuseLight() const {
    return mDiffuseLight;
}

const LightIntensity& Material::specularLight() const {
    return mSpecularLight;
}

void Material::setName(const std::string &name) {
    mName = name;
}

void Material::setAmbientLight(const LightIntensity &ambientLight) {
    mAmbientLight = ambientLight;
}

void Material::setSpecularLight(const LightIntensity &specularLight) {
    mSpecularLight = specularLight;
}

void Material::setDiffuseLight(const LightIntensity &diffuseLight) {
    mDiffuseLight = diffuseLight;
}

Material::Material(std::string name, LightIntensity lightIntensity, LightIntensity diffuseLight, LightIntensity specularLight, float shininess)
: mName(std::move(name)), mAmbientLight(lightIntensity), mDiffuseLight(diffuseLight), mSpecularLight(specularLight), mShininess(shininess)
{

}

const std::string &Material::name() const {
    return mName;
}

void Material::setShininess(float shininess) {
    mShininess = shininess;
}

float Material::shininess() const {
    return mShininess;
}

void Material::setTexture(std::shared_ptr<Texture> texture) {
    mTexture = std::move(texture);
}

const std::shared_ptr<Texture> &Material::texture() const {
    return mTexture;
}

const LightIntensity &Material::shadowLight() const {
    return mSpecularLight;
}

void Material::setShadowLight(const LightIntensity &shadowIntensity) {
    mShadowLightIntensity = shadowIntensity;
}
