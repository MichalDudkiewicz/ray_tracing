#pragma once

#include <string>
#include "mesh.hpp"

class ObjParser {
public:
    explicit ObjParser(std::string objString);

    Mesh parse();
private:
    std::string mObjString;
};

