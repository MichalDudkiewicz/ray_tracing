#include "mtl_parser.hpp"
#include <algorithm>
#include <sstream>
#include "material.hpp"
#include <utility>
#include <vector>

MtlParser::MtlParser(std::string mtlString)
: mMtlString(std::move(mtlString))
{
}

std::shared_ptr<Material> MtlParser::parse() const {
    auto material = std::make_shared<Material>();
    std::istringstream stream(mMtlString);
    std::string line;
    while(getline(stream, line))
    {
        line.erase(std::remove_if(line.begin(), line.end(), [](const auto ch){
            return isspace(ch) && ch != ' ';
        }), line.end());
        if (line.empty() || line.front() == '#' || line.front() == ' ')
        {
            continue;
        }
        std::string lineTitle = line.substr(0, line.find(' '));
        lineTitle.erase(remove_if(lineTitle.begin(), lineTitle.end(), isspace), lineTitle.end());
        std::string values = line.substr(line.find(' '));
        std::vector<std::string> numberStringValues;
        std::string temp;
        for(const char value : values){
            if(std::isspace(value)){
                if (!temp.empty())
                {
                    numberStringValues.push_back(temp);
                }
                temp = "";
            }
            else{
                temp.push_back(value);
            }

        }
        if (!temp.empty())
        {
            numberStringValues.push_back(temp);
        }
        if (lineTitle == "newmtl")
        {
            material->setName(numberStringValues.front());
        }
        else if (lineTitle == "Ka")
        {
            std::vector<float> floatValues;
            floatValues.reserve(numberStringValues.size());
            for (const auto& value : numberStringValues)
            {
                floatValues.push_back(std::stof(value));
            }
            if (floatValues.size() >= 3)
            {
                LightIntensity ambient(floatValues[0], floatValues[1], floatValues[2]);
                material->setAmbientLight(ambient);
            }
        }
        else if (lineTitle == "Kd")
        {
            std::vector<float> floatValues;
            floatValues.reserve(numberStringValues.size());
            for (const auto& value : numberStringValues)
            {
                floatValues.push_back(std::stof(value));
            }
            if (floatValues.size() >= 3)
            {
                LightIntensity diffuse(floatValues[0], floatValues[1], floatValues[2]);
                material->setDiffuseLight(diffuse);
            }
        }
        else if (lineTitle == "Ks")
        {
            std::vector<float> floatValues;
            floatValues.reserve(numberStringValues.size());
            for (const auto& value : numberStringValues)
            {
                floatValues.push_back(std::stof(value));
            }
            if (floatValues.size() >= 3)
            {
                LightIntensity specular(floatValues[0], floatValues[1], floatValues[2]);
                material->setSpecularLight(specular);
            }
        }
        else if (lineTitle == "Ns")
        {
            material->setShininess(std::stof(numberStringValues.front()));
        }
        else if (lineTitle == "map" || lineTitle == "map_Ka" || lineTitle == "map_Kd" || lineTitle == "map_Ks")
        {
            BMP image;
            image.ReadFromFile(numberStringValues.front().c_str());
            const auto texture = std::make_shared<Texture>(image);
            material->setTexture(texture);
        }
    }
    return material;
}
