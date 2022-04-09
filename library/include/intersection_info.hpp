#pragma once
#include "vector.hpp"
#include "light_intensity.hpp"
#include "material.hpp"

class IntersectionInfo
{
public:
    explicit IntersectionInfo(const Material& material, const Vector& position, const Vector& normal);

    const Vector& position() const;
    const Vector& normal() const;
    const Material& material() const;

private:
    Material mMaterial;
    Vector mPosition;
    Vector mNormal;
};

