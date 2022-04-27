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


    const LightIntensity& ambientLight() const;

    const LightIntensity& diffuseLight() const;

    const LightIntensity& specularLight() const;

    const LightIntensity& shadowLight() const;

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
    LightIntensity mShadowLightIntensity{0.5, 0.5, 0.5};
    bool mIsMirror;
};

