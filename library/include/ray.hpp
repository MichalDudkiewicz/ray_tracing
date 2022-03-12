#include "vector.hpp"

class Ray {
public:
    Ray();
    Ray(const Vector& origin, const Vector& direction, float distance = 0.0f);

    const Vector& origin() const;
    const Vector& direction() const;
    float distance() const;
    void setOrigin(const Vector& origin);
    void setDirection(const Vector& direction);
    void setDistance(float distance);

private:
    Vector mOrigin;
    Vector mDirection;
    float mDistance;
};