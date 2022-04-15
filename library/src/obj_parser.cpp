#include "obj_parser.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include <algorithm>
#include <sstream>
#include <fstream>
#include "material.hpp"
#include "mtl_parser.hpp"

ObjParser::ObjParser(std::string objString) : mObjString(std::move(objString))
{

}

Mesh ObjParser::parse() const {
    Mesh mesh;
    std::vector<Vector> vertexes;
    std::vector<Vector> normals;
    std::istringstream stream(mObjString);
    std::unique_ptr<MtlParser> mtlParser;
    std::string line;
    while(getline(stream, line))
    {
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
        if (lineTitle == "v")
        {
            std::vector<float> floatValues;
            floatValues.reserve(numberStringValues.size());
            for (const auto& value : numberStringValues)
            {
                floatValues.push_back(std::stof(value));
            }
            if (floatValues.size() >= 3)
            {
                vertexes.emplace_back(floatValues[0], floatValues[1], floatValues[2]);
            }
        }
        else if (lineTitle == "vn")
        {
            std::vector<float> floatValues;
            floatValues.reserve(numberStringValues.size());
            for (const auto& value : numberStringValues)
            {
                floatValues.push_back(std::stof(value));
            }
            if (floatValues.size() >= 3)
            {
                Vector normal(floatValues[0], floatValues[1], floatValues[2]);
                normal.normalize();
                normals.push_back(normal);
            }
        }
        else if (lineTitle == "f")
        {
            std::vector<int> intValues;
            int normalIndex;
            for (const auto& value : numberStringValues)
            {
                auto endIdx = value.rfind('/');
                auto beginIdx = value.find('/');
                int vertexIndex = std::stoi(value.substr(0, beginIdx)) - 1;
                normalIndex = std::stoi(value.substr(endIdx + 1)) - 1;
                intValues.push_back(vertexIndex);
            }
            if (intValues.size() >= 3)
            {
                auto triangle = std::make_shared<Triangle>(vertexes[intValues[0]], vertexes[intValues[1]], vertexes[intValues[2]], normals[normalIndex]);
                mesh.addPrimitive(triangle);
            }
        }
        else if (lineTitle == "usemtl")
        {
            std::string mtlLine;
            std::string mtl;
            std::ifstream mtlFile(numberStringValues.front() + ".mtl");
            if (mtlFile.is_open())
            {
                std::ostringstream buffer;
                while (getline(mtlFile, mtlLine))
                {
                    buffer << mtlLine << '\n';
                }
                mtl = buffer.str();
                mtlFile.close();
            }
            mtlParser = std::make_unique<MtlParser>(mtl);
        }
    }
    if (mtlParser)
    {
        const auto material = mtlParser->parse();
        mesh.setMaterial(material);
    }
    return mesh;
}
