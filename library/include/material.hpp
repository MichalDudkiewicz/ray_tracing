#pragma once
#include "light_intensity.hpp"
#include "texture.hpp"
#include <memory>

class Material {
public:
    Material(std::string name = "", LightIntensity ambientLight = {}, LightIntensity diffuseLight = {}, LightIntensity specularLight = {}, float shininess = 0.0f, bool isMirror = false);

    void setName(const std::string& name);

    void setAmbientLight(const LightIntensity& ambientIntensity);
    void setSpecularLight(const LightIntensity& specularIntensity);
    void setDiffuseLight(const LightIntensity& diffuseIntensity);
    void setShadowLight(const LightIntensity& shadowIntensity);
    void setShininess(float shininess);
    void setTexture(std::shared_ptr<Texture> texture);
    bool isMirror() const;

    void setMirror(bool isMirror);
    void setRefractionFactor(float refractionFactor);
    float refractionFactor() const;


    const LightIntensity& ambientLight() const;

    const LightIntensity& diffuseLight() const;

    const LightIntensity& specularLight() const;

    const LightIntensity& shadowLight() const;

    const LightIntensity& absorbedLight() const;

    void setAbsorbedLight(const LightIntensity& absorbedLight);

    void setLightEmitted(const LightIntensity &lightEmitted);

    const LightIntensity& lightEmitted() const;

    float shininess() const;

    const std::shared_ptr<Texture> &texture() const;

    const std::string& name() const;

private:
    std::string mName;
    LightIntensity mAmbientLight;
    LightIntensity mDiffuseLight;
    LightIntensity mSpecularLight;
    float mShininess;
    std::shared_ptr<Texture> mTexture;
    LightIntensity mShadowLightIntensity{0.05, 0.05, 0.05};
    bool mIsMirror;
    float mRefractionFactor = 1.0f;
    LightIntensity mLightEmitted;
    LightIntensity mLightAbsorbed{0.8f, 0.8f, 0.8f};
};

