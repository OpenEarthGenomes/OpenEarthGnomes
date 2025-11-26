#include "GenomeLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string GenomeLoader::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool GenomeLoader::saveToFile(const std::string& filepath, const std::string& genome_data) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        return false;
    }
    
    file << genome_data;
    return true;
}
