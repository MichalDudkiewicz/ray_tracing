#include "mesh.hpp"
#include <memory>
#include "primitive.hpp"

void Mesh::addPrimitive(std::shared_ptr<Primitive> primitive) {
    if (!mBoundingBox.has_value())
    {
        mBoundingBox = primitive->mBoundingBox;
    }

    if (mBoundingBox.has_value() && primitive->mBoundingBox.has_value())
    {
        if (mBoundingBox.value().lowerCorner().x() > primitive->mBoundingBox.value().lowerCorner().x())
        {
            mBoundingBox.value().lowerCorner().setX(primitive->mBoundingBox.value().lowerCorner().y());
        }
        if (mBoundingBox.value().lowerCorner().y() > primitive->mBoundingBox.value().lowerCorner().y())
        {
            mBoundingBox.value().lowerCorner().setY(primitive->mBoundingBox.value().lowerCorner().y());
        }
        if (mBoundingBox.value().lowerCorner().z() > primitive->mBoundingBox.value().lowerCorner().z())
        {
            mBoundingBox.value().lowerCorner().setZ(primitive->mBoundingBox.value().lowerCorner().z());
        }

        if (mBoundingBox.value().upperCorner().x() < primitive->mBoundingBox.value().upperCorner().x())
        {
            mBoundingBox.value().upperCorner().setX(primitive->mBoundingBox.value().upperCorner().y());
        }
        if (mBoundingBox.value().upperCorner().y() < primitive->mBoundingBox.value().upperCorner().y())
        {
            mBoundingBox.value().upperCorner().setY(primitive->mBoundingBox.value().upperCorner().y());
        }
        if (mBoundingBox.value().upperCorner().z() < primitive->mBoundingBox.value().upperCorner().z())
        {
            mBoundingBox.value().upperCorner().setZ(primitive->mBoundingBox.value().upperCorner().z());
        }
    }

    mPrimitives.push_back(std::move(primitive));
}

const std::vector<std::shared_ptr<Primitive>> &Mesh::primitives() const {
    return mPrimitives;
}

const std::string &Mesh::groupName() const {
    return mGroupName;
}

Mesh::Mesh(std::string groupName) : mGroupName(std::move(groupName)), mBoundingBox()
{

}

std::optional<std::tuple<Vector, Vector, std::shared_ptr<Primitive>>> Mesh::intersection(const Ray &ray) const {
    float minDistance = ray.distance();
    std::optional<std::tuple<Vector, Vector, std::shared_ptr<Primitive>>> intersectionData;
    for (const auto& primitive : mPrimitives)
    {
        const auto intersection = primitive->intersection(ray);
        if (intersection.has_value())
        {
            const auto& minZIntersectionPoint = intersection.value();
            const float newDistance = (minZIntersectionPoint - ray.origin()).length();
            if (newDistance < minDistance)
            {
                intersectionData = std::make_tuple(minZIntersectionPoint, primitive->normal(minZIntersectionPoint), primitive);
                minDistance = newDistance;
            }
        }
    }
    return intersectionData;
}

const Material &Mesh::material() const {
    return *mMaterial;
}

void Mesh::setMaterial(const std::shared_ptr<Material> &material) {
    mMaterial = material;
}

bool Mesh::intersectsBoundingBox(const Ray &ray) const {
    if (mBoundingBox.has_value())
    {
        return mBoundingBox.value().intersects(ray);
    }
    return false;
}

bool Mesh::hasBoundingBox() const {
    return mBoundingBox.has_value();
}
