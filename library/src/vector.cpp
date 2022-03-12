#include "vector.hpp"

#include <cmath>

namespace
{
    constexpr float kExponentTwo = 2.0f;
}

Vector::Vector(float x, float y, float z) : mX(x), mY(y), mZ(z) {
}

float Vector::x() const {
    return mX;
}

float Vector::y() const {
    return mY;
}

float Vector::z() const {
    return mZ;
}

void Vector::setX(float x) {
    mX = x;
}

void Vector::setY(float y) {
    mY = y;
}

void Vector::setZ(float z) {
    mZ = z;
}

float Vector::length() const {
    return sqrtf(powf(mX, kExponentTwo) + powf(mY, kExponentTwo) + powf(mZ, kExponentTwo));
}

float Vector::lengthSquared() const {
    return powf(length(), kExponentTwo);
}

bool Vector::isUnit() const {
    constexpr float kUnitLength = 1.0f;
    return length() == kUnitLength;
}
