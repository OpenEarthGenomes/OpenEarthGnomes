#include "DatabaseManager.h"
#include "GenomeLoader.h"
#include <iostream>
#include <string>
#include <vector>

using namespace OpenEarthGenomes;

void printUsage(const char* programName) {
    std::cout << "OpenEarthGenomes - Genomadatbázis kezelő\n"
              << "Használat:\n"
              << "  " << programName << " [OPCIÓK]\n\n"
              << "Opciók:\n"
              << "  --help              Segítség megjelenítése\n"
              << "  --config FILE       Konfigurációs fájl megadása (alapértelmezett: config.ini)\n"
              << "  --load FILE         FASTA fájl betöltése\n"
              << "  --load-dir DIR      Könyvtár FASTA fájljainak betöltése\n"
              << "  --search SPECIES    Faj keresése\n"
              << "  --list              Összes faj listázása\n"
              << "  --stats             Adatbázis statisztikák\n"
              << "  --init              Adatbázis inicializálása\n"
              << std::endl;
}

void printStats(DatabaseManager& db) {
    std::cout << "\n=== Adatbázis Statisztikák ===\n";
    std::cout << "Összes genom: " << db.getGenomeCount() << "\n";
    
    auto species = db.getSpeciesList();
    std::cout << "Fajok száma: " << species.size() << "\n";
    
    if (!species.empty()) {
        std::cout << "\nElső 10 faj:\n";
        for (size_t i = 0; i < std::min(species.size(), size_t(10)); ++i) {
            std::cout << "  " << (i+1) << ". " << species[i] << "\n";
        }
    }
    std::cout << std::endl;
}

void searchSpecies(DatabaseManager& db, const std::string& searchTerm) {
    std::cout << "\nKeresés: '" << searchTerm << "'\n";
    std::cout << "========================\n";
    
    auto results = db.findBySpecies(searchTerm);
    
    if (results.empty()) {
        std::cout << "Nincs találat.\n";
        return;
    }
    
    std::cout << "Találatok (" << results.size() << " db):\n";
    for (const auto& genome : results) {
        std::cout << "ID: " << genome.id 
                  << " | Faj: " << genome.species_name;
        
        if (!genome.common_name.empty()) {
            std::cout << " (" << genome.common_name << ")";
        }
        
        std::cout << " | Hossz: " << genome.sequence_length << " bp";
        
        if (!genome.file_source.empty()) {
            std::cout << " | Forrás: " << genome.file_source;
        }
        
        std::cout << "\n";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "OpenEarthGenomes v1.0 - A Föld élőlényeinek genomtára\n";
    std::cout << "=====================================================\n\n";

    // Alapértelmezett konfiguráció
    std::string configFile = "config.ini";
    
    // Argumentumok feldolgozása
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    // Konfiguráció betöltése
    auto config = loadConfigFromFile(configFile);
    DatabaseManager db(config);
    
    // Kapcsolódás az adatbázishoz
    if (!db.connect()) {
        std::cerr << "HIBA: Nem sikerült kapcsolódni az adatbázishoz!\n";
        std::cerr << "Ellenőrizd a MySQL szerver státuszát és a config.ini fájlt.\n";
        std::cerr << "Hiba: " << db.getLastError() << std::endl;
        return 1;
    }

    // Argumentumok feldolgozása
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "--help") {
            printUsage(argv[0]);
            return 0;
            
        } else if (arg == "--config" && i + 1 < argc) {
            configFile = argv[++i];
            
        } else if (arg == "--init") {
            std::cout << "Adatbázis inicializálása...\n";
            if (db.createTables()) {
                std::cout << "Sikeres inicializálás!\n";
            } else {
                std::cerr << "Inicializálási hiba: " << db.getLastError() << std::endl;
                return 1;
            }
            
        } else if (arg == "--load" && i + 1 < argc) {
            std::string filePath = argv[++i];
            std::cout << "FASTA fájl betöltése: " << filePath << "\n";
            
            GenomeLoader loader(db);
            if (loader.loadFASTAFile(filePath)) {
                std::cout << "Sikeres betöltés!\n";
                std::cout << "Betöltött szekvenciák: " << loader.getLoadedSequences() << "\n";
                std::cout << "Összes bázispár: " << loader.getTotalBasePairs() << "\n";
            } else {
                std::cerr << "Betöltési hiba: " << loader.getLastError() << std::endl;
            }
            
        } else if (arg == "--load-dir" && i + 1 < argc) {
            std::string dirPath = argv[++i];
            std::cout << "Könyvtár FASTA fájljainak betöltése: " << dirPath << "\n";
            
            GenomeLoader loader(db);
            if (loader.loadFromDirectory(dirPath)) {
                std::cout << "Sikeres betöltés!\n";
                std::cout << "Betöltött szekvenciák: " << loader.getLoadedSequences() << "\n";
                std::cout << "Összes bázispár: " << loader.getTotalBasePairs() << "\n";
            } else {
                std::cerr << "Betöltési hiba: " << loader.getLastError() << std::endl;
            }
            
        } else if (arg == "--search" && i + 1 < argc) {
            std::string searchTerm = argv[++i];
            searchSpecies(db, searchTerm);
            
        } else if (arg == "--list") {
            auto species = db.getSpeciesList();
            std::cout << "\nÖsszes faj (" << species.size() << " db):\n";
            std::cout << "====================\n";

            for (size_t i = 0; i < species.size(); ++i) {
                std::cout << (i+1) << ". " << species[i] << "\n";
            }
            std::cout << std::endl;
            
        } else if (arg == "--stats") {
            printStats(db);
            
        } else {
            std::cerr << "Ismeretlen argumentum: " << arg << std::endl;
            printUsage(argv[0]);
            return 1;
        }
    }
    
    return 0;
}
