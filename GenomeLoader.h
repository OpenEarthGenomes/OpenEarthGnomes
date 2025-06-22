#pragma once
#include <fstream>
#include <sstream>
#include <string>

class GenomeLoader {
public:
    std::string loadFromFile(const std::string& filePath);
    void saveToFile(const std::string& filePath, const std::string& genomeData);
};

// Implementáció
std::string GenomeLoader::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) throw std::runtime_error("Fájl megnyitása sikertelen: " + filePath);
    
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void GenomeLoader::saveToFile(const std::string& filePath, const std::string& genomeData) {
    std::ofstream file(filePath);
    if (!file) throw std::runtime_error("Fájl létrehozása sikertelen: " + filePath);
    file << genomeData;
}
