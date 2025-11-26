#include <iostream>
#include "DatabaseManager.h"
#include "GenomeLoader.h"
#include "INIReader.h"

int main() {
    try {
        // INI fájl betöltése
        INIReader reader("config.ini");
        if (reader.ParseError() != 0) {
            std::cerr << "❌ ERROR: Config file loading failed" << std::endl;
            return 1;
        }
        
        // Adatok kinyerése a konfigurációból
        std::string host = reader.Get("database", "host", "localhost");
        std::string user = reader.Get("database", "user", "root");
        std::string password = reader.Get("database", "password", "");
        std::string database_name = reader.Get("database", "database_name", "EarthGenomes");
        
        std::string genome_path = reader.Get("genome", "genome_path", "./genomes");
        std::string default_genome = genome_path + "/Triticum_aestivum.fasta";
        
        // Adatbázis kapcsolat inicializálása
        DatabaseManager dbManager(host, user, password, database_name);
        std::cout << "✅ Database initialized successfully!" << std::endl;
        
        // Genom betöltése FASTA fájlból
        GenomeLoader loader;
        std::string genomeData = loader.loadFromFile(default_genome);
        std::cout << "✅ Genome loaded successfully!" << std::endl;
        
        // Genom feltöltése az adatbázisba
        dbManager.uploadGenome("Wheat", "Triticum aestivum", genomeData);
        std::cout << "✅ Genome uploaded to database successfully!" << std::endl;

        // Genom visszaolvasása
        std::string downloadedGenome = dbManager.downloadGenome("Triticum aestivum");
        loader.saveToFile("downloaded_wheat.fasta", downloadedGenome);
        std::cout << "✅ Genome downloaded successfully: downloaded_wheat.fasta" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "❌ ERROR: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "🎉 Program completed successfully!" << std::endl;
    return 0;
}
