#include "GenomeLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string GenomeLoader::loadFromFile(const std::string& filePath) {
    // Fájl megnyitása bináris módban
    std::ifstream file(filePath, std::ios::binary);
    
    if (!file.is_open()) {
        throw std::runtime_error("Hiba: Nem sikerült megnyitni a fájlt - " + filePath);
    }

    // Fájl tartalmának beolvasása stringbe
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void GenomeLoader::saveToFile(const std::string& filePath, const std::string& genomeData) {
    // Fájl létrehozása és írás
    std::ofstream file(filePath, std::ios::binary);
    
    if (!file.is_open()) {
        throw std::runtime_error("Hiba: Nem sikerült létrehozni a fájlt - " + filePath);
    }
    
    file.write(genomeData.c_str(), genomeData.size());
}
