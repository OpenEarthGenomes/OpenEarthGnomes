#pragma once
#include <string>

class GenomeLoader {
public:
    std::string loadFromFile(const std::string& filepath);
    bool saveToFile(const std::string& filepath, const std::string& genome_data);
};
