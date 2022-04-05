#pragma once

#include "primitive.hpp"
#include <memory>
#include <vector>

class Mesh {
public:
    void addPrimitive(std::shared_ptr<Primitive> primitive);

    const std::vector<std::shared_ptr<Primitive>>& primitives() const;

private:
    std::vector<std::shared_ptr<Primitive>> mPrimitives;
};
