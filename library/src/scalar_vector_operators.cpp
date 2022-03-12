#include "scalar_vector_operators.hpp"

Vector operator*(const float scalar, const Vector& vector)
{
    return {vector.x() * scalar, vector.y() * scalar, vector.z() * scalar};
}