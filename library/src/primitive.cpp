#include "primitive.hpp"

const Material &Primitive::material() const {
    return *mMaterial;
}

void Primitive::setMaterial(const std::shared_ptr<Material> &material) {
    mMaterial = material;
}
