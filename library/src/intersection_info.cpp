#include "intersection_info.hpp"

IntersectionInfo::IntersectionInfo(Material material, const Vector &position, const Vector &normal)
: mMaterial(std::move(material)), mPosition(position), mNormal(normal)
{

}

const Vector &IntersectionInfo::position() const {
    return mPosition;
}

const Vector &IntersectionInfo::normal() const {
    return mNormal;
}

const Material &IntersectionInfo::material() const {
    return mMaterial;
}
