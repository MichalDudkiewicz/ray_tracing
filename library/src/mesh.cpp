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
