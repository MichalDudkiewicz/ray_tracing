#pragma once
#include "light_intensity.hpp"

class Material {
public:
    Material(std::string name = "", LightIntensity ambientLight = {}, LightIntensity diffuseLight = {}, LightIntensity specularLight = {}, float shininess = 0.0f);

    void setName(const std::string& name);

    void setAmbientLight(const LightIntensity& ambientIntensity);
    void setSpecularLight(const LightIntensity& specularIntensity);
    void setDiffuseLight(const LightIntensity& diffuseIntensity);
    void setShininess(float shininess);

    const LightIntensity& ambientLight() const;

    const LightIntensity& diffuseLight() const;

    const LightIntensity& specularLight() const;

    float shininess() const;

    const std::string& name() const;

private:
    std::string mName;
    LightIntensity mAmbientLight;
    LightIntensity mDiffuseLight;
    LightIntensity mSpecularLight;
    float mShininess;
};
