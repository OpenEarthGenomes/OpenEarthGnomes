#include <iostream>
#include "DatabaseManager.h"
#include "GenomeLoader.h"

int main() {
    try {
        // Egyszerű, keményen kódolt értékek
        DatabaseManager dbManager("localhost", "root", "", "EarthGenomes");
        std::cout << "✅ Database initialized successfully!" << std::endl;
        
        // Genom betöltése
        GenomeLoader loader;
        std::string genomeData = loader.loadFromFile("genomes/Triticum_aestivum.fasta");
        std::cout << "✅ Genome loaded successfully!" << std::endl;
        
        // Genom feltöltése
        dbManager.uploadGenome("Wheat", "Triticum aestivum", genomeData);
        std::cout << "✅ Genome uploaded to database successfully!" << std::endl;

        // Genom letöltése
        std::string downloadedGenome = dbManager.downloadGenome("Triticum aestivum");
        loader.saveToFile("downloaded_wheat.fasta", downloadedGenome);
        std::cout << "✅ Genome downloaded successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "❌ ERROR: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "🎉 Program completed successfully!" << std::endl;
    return 0;
}
