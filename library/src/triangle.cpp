#include "triangle.hpp"
#include "surface.hpp"

#define MINUS_ZERO -0.0001

Triangle::Triangle(const Vector &a, const Vector &b, const Vector &c, const Vector &normal)
: mA(a), mB(b), mC(c), mNormal(normal)
{

}

Triangle::Triangle(const Vector &a, const Vector &b, const Vector &c)
        : mA(a), mB(b), mC(c), mNormal((mB - mA).crossProduct(mC - mA))
{
}

std::optional<Vector> Triangle::intersection(const Ray &ray) const {
    Surface triangleSurface(mA, mNormal);
    auto surfaceIntersectionPoint = triangleSurface.intersection(ray);
    if (surfaceIntersectionPoint.has_value() && !isInsideTriangle(surfaceIntersectionPoint.value()))
    {
        return std::nullopt;
    }
    return surfaceIntersectionPoint;
}

bool Triangle::isInsideTriangle(const Vector &point) const {
    const Vector pa = mA - point;
    const Vector pb = mB - point;
    const Vector pc = mC - point;
    Vector x = pa.crossProduct(pb);

    if(x.dotProduct(mNormal)<MINUS_ZERO)
    {
        return false;
    }
    else
    {
        x = pb.crossProduct(pc);
        if(x.dotProduct(mNormal)<MINUS_ZERO)
        {
            return false;
        }
        else
        {
            x = pc.crossProduct(pa);
            if (x.dotProduct(mNormal) < MINUS_ZERO)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}

Vector Triangle::normal(const Vector& /*intersectionPoint*/) const {
    return mNormal;
}

bool Triangle::operator==(const Triangle &other) const {
    return mNormal == other.mNormal && mA == other.mA && mB == other.mB && mC == other.mC;
}

bool Triangle::operator!=(const Triangle &other) const {
    return !(*this==other);
}
