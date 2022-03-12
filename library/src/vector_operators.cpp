#include "vector_operators.hpp"

Vector operator*(const float scalar, const Vector& vector)
{
    return {vector.x() * scalar, vector.y() * scalar, vector.z() * scalar};
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    os << "Vector[" << vector.x() << ',' << vector.y() << ',' << vector.z() << ']';
    return os;
}