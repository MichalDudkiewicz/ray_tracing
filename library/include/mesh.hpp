#pragma once

#include "primitive.hpp"
#include <memory>
#include <vector>

class Mesh {
public:
    explicit Mesh(std::string groupName = "");

public:
    void addPrimitive(std::shared_ptr<Primitive> primitive);

    const std::vector<std::shared_ptr<Primitive>>& primitives() const;

    const std::string& groupName() const;

    std::optional<std::pair<Vector, Vector>> intersection(const Ray &ray) const;

    const Material& material() const;

    void setMaterial(const std::shared_ptr<Material> &material);

private:
    std::vector<std::shared_ptr<Primitive>> mPrimitives;
    std::string mGroupName;
    std::shared_ptr<Material> mMaterial;
};
