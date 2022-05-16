#pragma once

#include "primitive.hpp"
#include "cuboid.hpp"
#include <memory>
#include <vector>

class Mesh {
public:
    explicit Mesh(std::string groupName = "");

public:
    void addPrimitive(std::shared_ptr<Primitive> primitive);

    const std::vector<std::shared_ptr<Primitive>>& primitives() const;

    const std::string& groupName() const;

    std::optional<std::tuple<Vector, Vector, std::shared_ptr<Primitive>>> intersection(const Ray &ray) const;

    bool intersectsBoundingBox(const Ray &ray) const;

    const Material& material() const;

    void setMaterial(const std::shared_ptr<Material> &material);

    bool hasBoundingBox() const;

private:
    std::vector<std::shared_ptr<Primitive>> mPrimitives;
    std::string mGroupName;
    std::shared_ptr<Material> mMaterial;
    std::optional<Cuboid> mBoundingBox;
};
