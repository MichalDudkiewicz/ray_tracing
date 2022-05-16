#include "primitive.hpp"

Primitive::Primitive(const Vector &lowerCorner, const Vector &upperCorner) {
    mBoundingBox = Cuboid{lowerCorner, upperCorner};
}
