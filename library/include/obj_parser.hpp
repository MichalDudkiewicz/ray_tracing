#pragma once

#include <string>
#include "mesh.hpp"

class ObjParser {
public:
    explicit ObjParser(std::string objString);

    Mesh parse() const;
private:
    std::string mObjString;
};

