#pragma once

#include "vector.hpp"

#include <ostream>

Vector operator*(float scalar, const Vector& vector);
std::ostream& operator<<(std::ostream& os, const Vector& dt);