#pragma once

#include "material.hpp"
#include <memory>

class MtlParser {
public:
    explicit MtlParser(std::string mtlString);

    std::shared_ptr<Material> parse() const;
private:
    std::string mMtlString;
};