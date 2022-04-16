#include "mesh.hpp"
#include <memory>
#include "primitive.hpp"

void Mesh::addPrimitive(std::shared_ptr<Primitive> primitive) {
    mPrimitives.push_back(std::move(primitive));
}

const std::vector<std::shared_ptr<Primitive>> &Mesh::primitives() const {
    return mPrimitives;
}

const std::string &Mesh::groupName() const {
    return mGroupName;
}

Mesh::Mesh(std::string groupName) : mGroupName(std::move(groupName))
{

}

std::optional<std::tuple<Vector, Vector, std::shared_ptr<Primitive>>> Mesh::intersection(const Ray &ray) const {
    float minZIntersection = (ray.origin() + ray.direction()*ray.distance()).z();
    std::optional<std::tuple<Vector, Vector, std::shared_ptr<Primitive>>> intersectionData;
    for (const auto& primitive : mPrimitives)
    {
        const auto intersection = primitive->intersection(ray);
        if (intersection.has_value())
        {
            const auto& minZIntersectionPoint = intersection.value();
            if (minZIntersectionPoint.z() > minZIntersection)
            {
                intersectionData = std::make_tuple(minZIntersectionPoint, primitive->normal(minZIntersectionPoint), primitive);
                minZIntersection = minZIntersectionPoint.z();
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
