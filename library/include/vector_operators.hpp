#pragma once

#include "vector.hpp"

#include <ostream>

Vector operator*(float scalar, const Vector& vector);
std::ostream& operator<<(std::ostream& os, const Vector& vector);
float angleBetween(const Vector& v1, const Vector& v2);