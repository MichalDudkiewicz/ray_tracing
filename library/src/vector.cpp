#include "vector.hpp"

#include <cmath>
#include <stdexcept>

namespace
{
    constexpr float kExponentTwo = 2.0f;
}

Vector::Vector(const float x, const float y, const float z) : mX(x), mY(y), mZ(z) {
}

Vector::Vector(const Vector &other) = default;

float Vector::x() const {
    return mX;
}

float Vector::y() const {
    return mY;
}

float Vector::z() const {
    return mZ;
}

void Vector::setX(const float x) {
    mX = x;
}

void Vector::setY(const float y) {
    mY = y;
}

void Vector::setZ(const float z) {
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

Vector& Vector::operator=(const Vector &other) = default;

Vector Vector::operator*(const float scalar) const {
    return {mX * scalar, mY * scalar, mZ * scalar};
}

void Vector::negate() {
    *this=*this*(-1.0f);
}

Vector Vector::operator/(const float scalar) const {
    if (scalar == 0.0f)
    {
        throw std::runtime_error("division by zero");
    }
    return *this*(1.0f/scalar);
}

Vector Vector::operator+(const Vector &other) const {
    return {mX + other.mX, mY + other.mY, mZ + other.mZ};
}

Vector Vector::operator-(const Vector &other) const {
    return {mX - other.mX, mY - other.mY, mZ - other.mZ};
}

Vector Vector::operator*(const Vector &other) const {
    return {mX * other.mX, mY * other.mY, mZ * other.mZ};
}

Vector Vector::operator/(const Vector &other) const {
    if (other.mX == 0.0f || other.mY == 0.0f || other.mZ == 0.0f)
    {
        throw std::runtime_error("division by zero");
    }
    return {mX / other.mX, mY / other.mY, mZ / other.mZ};
}

Vector Vector::crossProduct(const Vector &other) const {
    return {mY * other.mZ - mZ * other.mY, mZ * other.mX - mX * other.mZ, mX * other.mY - mY * other.mX};
}

float Vector::dotProduct(const Vector &other) const {
    return mX * other.mX + mY * other.mY + mZ * other.mZ;
}

Vector Vector::normalize() const {
    const float len = length();
    if (len != 0.0f)
    {
        return {*this/len};
    }
    throw std::runtime_error("could not normalize");
}

Vector Vector::reflect(const Vector &normal) const {
    return *this - (normal * this->dotProduct(normal) * 2.0f);
}

Vector Vector::lerp(const Vector &other, const float t) const {
    return {mX + t * (other.mX - mX), mY + t * (other.mY - mY), mZ + t * (other.mZ - mZ)};
}

bool Vector::operator==(const Vector &other) const {
    return mX == other.mX && mY == other.mY && mZ == other.mZ;
}

const float &Vector::operator[](int i) const {
    switch (i) {
        case 0:
            return mX;
        case 1:
            return mY;
        case 2:
            return mZ;
        default:
            throw std::runtime_error("out of range");
    }
}

float &Vector::operator[](int i) {
    switch (i) {
        case 0:
            return mX;
        case 1:
            return mY;
        case 2:
            return mZ;
        default:
            throw std::runtime_error("out of range");
    }
}


