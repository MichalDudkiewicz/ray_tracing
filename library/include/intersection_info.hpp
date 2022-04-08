#pragma once
#include "vector.hpp"
#include "light_intensity.hpp"

struct IntersectionInfo
{
    Vector position;
    Vector normalVector;
    float diffuseCoeff;
};
