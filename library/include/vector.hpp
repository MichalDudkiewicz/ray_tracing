#pragma once

class Vector {
public:
    Vector(float x = 0, float y = 0, float z = 0);
    Vector(const Vector& other);

    float x() const;
    float y() const;
    float z() const;
    void setX(float x);
    void setY(float y);
    void setZ(float x);

    float length() const;
    float lengthSquared() const;
    bool isUnit() const;

    Vector& operator=(const Vector& other);
    Vector operator*(float scalar) const;
    void negate();
    Vector operator/(float scalar) const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(const Vector& other) const;
    Vector operator/(const Vector& other) const;

    Vector crossProduct(const Vector& other) const;
    float dotProduct(const Vector& other) const;

    Vector normalize() const;
    Vector reflect(const Vector& normal) const;
    Vector lerp(const Vector& other, float t) const;

    bool operator==(const Vector& other) const;

    const float& operator[](int i) const;

    float& operator[](int i);

private:
    float mX;
    float mY;
    float mZ;
};

