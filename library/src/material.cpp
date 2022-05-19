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

void Material::setLightEmitted(const LightIntensity &lightEmitted) {
    mLightEmitted = lightEmitted;
}

Material::Material(std::string name, LightIntensity lightIntensity, LightIntensity diffuseLight, LightIntensity specularLight, float shininess, bool isMirror)
: mName(std::move(name)), mAmbientLight(lightIntensity), mDiffuseLight(diffuseLight), mSpecularLight(specularLight), mShininess(shininess), mIsMirror(isMirror)
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
    return mShadowLightIntensity;
}

void Material::setShadowLight(const LightIntensity &shadowIntensity) {
    mShadowLightIntensity = shadowIntensity;
}

void Material::setMirror(bool isMirror) {
    mIsMirror = isMirror;
}

bool Material::isMirror() const {
    return mIsMirror;
}

void Material::setRefractionFactor(float refractionFactor) {
    mRefractionFactor = refractionFactor;
}

float Material::refractionFactor() const {
    return mRefractionFactor;
}

const LightIntensity &Material::lightEmitted() const {
    return mLightEmitted;
}

void Material::setAbsorbedLight(const LightIntensity &absorbedLight) {
    mLightAbsorbed = absorbedLight;
}

const LightIntensity &Material::absorbedLight() const {
    return mLightAbsorbed;
}
