#include <iostream>
#include "DatabaseManager.h"
#include "GenomeLoader.h"

int main() {
    try {
        // Adatbázis kapcsolat inicializálása
        DatabaseManager dbManager("localhost", "root", "", "EarthGenomes");
        
        // Genom betöltése FASTA fájlból
        GenomeLoader loader;
        std::string genomeData = loader.loadFromFile("genomes/Triticum_aestivum.fasta");
        
        // Genom feltöltése az adatbázisba
        dbManager.uploadGenome("Búza", "Triticum aestivum", genomeData);
        std::cout << "Genom sikeresen feltöltve!\n";

        // Genom visszaolvasása
        std::string downloadedGenome = dbManager.downloadGenome("Triticum aestivum");
        loader.saveToFile("downloaded_wheat.fasta", downloadedGenome);
        std::cout << "Genom sikeresen letöltve: downloaded_wheat.fasta\n";

    } catch (const std::exception& e) {
        std::cerr << "Hiba: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
