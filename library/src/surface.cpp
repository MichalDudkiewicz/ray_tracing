#include "surface.hpp"
#include <limits>

namespace
{
    const Vector xAxis(1.0f);
    const Vector yAxis(0.0f, 1.0f);
    const Vector zAxis(0.0f, 0.0f, 1.0f);
    constexpr float thresh = 0.001f;
    constexpr float expandFactor = 2.5f;
}

Surface::Surface(const Vector &point, const Vector &normal) : mPoint(point), mNormal(normal) {
    const Vector moveAlongX = xAxis.crossProduct(mNormal);
    const Vector moveAlongY = yAxis.crossProduct(mNormal);
    const Vector moveAlongZ = zAxis.crossProduct(mNormal);

    std::vector<Vector> points;
    const Vector movedPositiveAlongX = mPoint + moveAlongX * expandFactor;
    points.push_back(movedPositiveAlongX);
    const Vector movedPositiveAlongY = mPoint + moveAlongY * expandFactor;
    points.push_back(movedPositiveAlongY);
    const Vector movedPositiveAlongZ = mPoint + moveAlongZ * expandFactor;
    points.push_back(movedPositiveAlongZ);
    const Vector movedNegativeAlongX = mPoint - moveAlongX * expandFactor;
    points.push_back(movedNegativeAlongX);
    const Vector movedNegativeAlongY = mPoint - moveAlongY * expandFactor;
    points.push_back(movedNegativeAlongY);
    const Vector movedNegativeAlongZ = mPoint - moveAlongZ * expandFactor;
    points.push_back(movedNegativeAlongZ);

    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float minZ = std::numeric_limits<float>::max();

    float maxX = -std::numeric_limits<float>::max();
    float maxY = -std::numeric_limits<float>::max();
    float maxZ = -std::numeric_limits<float>::max();

    for (const auto& p : points)
    {
        if (p.x() < minX)
        {
            minX = p.x();
        }
        if (p.y() < minY)
        {
            minY = p.y();
        }
        if (p.z() < minZ)
        {
            minZ = p.z();
        }
        if (p.x() > maxX)
        {
            maxX = p.x();
        }
        if (p.y() > maxY)
        {
            maxY = p.y();
        }
        if (p.z() > maxZ)
        {
            maxZ = p.z();
        }
    }

    minZ -= thresh;
    minY -= thresh;
    minX -= thresh;

    maxZ += thresh;
    maxY += thresh;
    maxX += thresh;

    const Vector lowerCorner(minX, minY, minZ);
    const Vector upperCorner(maxX, maxY, maxZ);

    mBoundingBox = Cuboid{lowerCorner, upperCorner};
}

float Surface::shift() const {
    return mNormal.dotProduct(mPoint);
}

const Vector &Surface::point() {
    return mPoint;
}

Vector Surface::normal(const Vector& /*intersectionPoint*/) const {
    return mNormal;
}

std::optional<Vector> Surface::intersection(const Ray &ray) const {
    const auto t = shift();
    Vector V = ray.direction().normalize();
    const auto nDotV = mNormal.dotProduct(V);
    // ray is parallel to surface or ray intersects surface before its start point
    if (nDotV != 0) {
//        Vector p0l0 = ray.origin() - mPoint;
//        const auto a = p0l0.dotProduct(mNormal) / nDotV;
        const auto a = (t - mNormal.dotProduct(ray.origin())) / nDotV;
        if (a > 0 && a < ray.distance())
        {
            return ray.origin() + V * a;
        }
        else
        {
            return std::nullopt;
        }
    }
    else
    {
        return std::nullopt;
    }
}
