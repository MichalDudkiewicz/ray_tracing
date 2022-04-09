#include "vector_operators.hpp"

#include <cmath>

Vector operator*(const float scalar, const Vector& vector)
{
    return {vector.x() * scalar, vector.y() * scalar, vector.z() * scalar};
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    os << "Vector[" << vector.x() << ',' << vector.y() << ',' << vector.z() << ']';
    return os;
}

float angleBetween(const Vector& v1, const Vector& v2)
{
    return asinf(v1.crossProduct(v2).length() / (v1.length() * v2.length())) * 180/M_PI;
}