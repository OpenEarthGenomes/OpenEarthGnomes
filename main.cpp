              #include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class SimpleGenomeStorage {
private:
    std::string storagePath;

public:
    SimpleGenomeStorage(const std::string& path = "./genomes/") : storagePath(path) {
        // Create directory if it doesn't exist
        fs::create_directories(storagePath);
    }

    bool saveGenome(const std::string& species, const std::string& scientificName, const std::string& genomeData) {
        std::string filename = storagePath + scientificName + ".fasta";
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "❌ Cannot open file for writing: " << filename << std::endl;
            return false;
        }
        
        file << ">" << species << " (" << scientificName << ")\n";
        file << genomeData;
        file.close();
        
        std::cout << "✅ Genome saved to: " << filename << std::endl;
        return true;
    }

    std::string loadGenome(const std::string& scientificName) {
        std::string filename = storagePath + scientificName + ".fasta";
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "❌ Cannot open file for reading: " << filename << std::endl;
            return "";
        }
        
        std::string content((std::istreambuf_iterator<char>(file)), 
                           std::istreambuf_iterator<char>());
        file.close();
        
        std::cout << "✅ Genome loaded from: " << filename << std::endl;
        return content;
    }

    void listAllGenomes() {
        std::cout << "📁 Available genomes:" << std::endl;
        for (const auto& entry : fs::directory_iterator(storagePath)) {
            if (entry.path().extension() == ".fasta") {
                std::cout << "   • " << entry.path().filename() << std::endl;
            }
        }
    }
};

class GenomeLoader {
public:
    std::string loadFromFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filepath);
        }
        
        std::string content((std::istreambuf_iterator<char>(file)), 
                           std::istreambuf_iterator<char>());
        return content;
    }

    bool saveToFile(const std::string& filepath, const std::string& genomeData) {
        std::ofstream file(filepath);
        if (!file.is_open()) {
            return false;
        }
        
        file << genomeData;
        return true;
    }
};

int main() {
    std::cout << "🧬 OpenEarthGenomes - File-Based Genome Storage" << std::endl;
    std::cout << "=============================================" << std::endl;
    
    try {
        SimpleGenomeStorage storage;
        GenomeLoader loader;
        
        // Példa genom betöltése
        std::string genomeData = "ATCGATCGATCGATCGATCGATCG\nGCTAGCTAGCTAGCTAGCTAGCTA";
        
        // Genom mentése fájlba
        storage.saveGenome("Wheat", "Triticum_aestivum", genomeData);
        storage.saveGenome("Corn", "Zea_mays", "CGTACGTACGTACGTACGTACGTACGTA");
        
        // Genom visszatöltése
        std::string loadedGenome = storage.loadGenome("Triticum_aestivum");
        if (!loadedGenome.empty()) {
            std::cout << "✅ Genome storage test successful!" << std::endl;
        }
        
        // Összes genom listázása
        storage.listAllGenomes();
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "🎉 Program completed successfully!" << std::endl;
    return 0;
}
