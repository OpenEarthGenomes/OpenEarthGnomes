#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>

// MySQL Connector/C++ includes
#include <mysqlx/xdevapi.h>

namespace OpenEarthGenomes {

struct GenomeRecord {
    int id;
    std::string species_name;
    std::string common_name;
    std::string sequence;
    std::string file_source;
    std::string upload_date;
    size_t sequence_length;
};

struct DatabaseConfig {
    std::string host = "localhost";
    std::string user = "root";
    std::string password = "";
    std::string database = "EarthGenomes";
    int port = 3306;
};

class DatabaseManager {
public:
    explicit DatabaseManager(const DatabaseConfig& config);
    ~DatabaseManager();

    // Kapcsolat kezelése
    bool connect();
    void disconnect();
    bool isConnected() const;

    // Adatbázis műveleték
    bool createTables();
    bool insertGenome(const GenomeRecord& genome);
    std::vector<GenomeRecord> findBySpecies(const std::string& species_name);
    std::vector<GenomeRecord> findByCommonName(const std::string& common_name);
    std::optional<GenomeRecord> findById(int id);
    std::vector<GenomeRecord> getAllGenomes();
    
    // Statisztikák
    size_t getGenomeCount();
    std::vector<std::string> getSpeciesList();
    
    // Hibakezelés
    std::string getLastError() const;

private:
    DatabaseConfig m_config;
    std::unique_ptr<mysqlx::Session> m_session;
    std::string m_lastError;
    bool m_connected;

    // Segéd függvények
    void setLastError(const std::string& error);
    GenomeRecord resultToGenome(const mysqlx::Row& row);
};

// Konfigurációs fájl betöltése
DatabaseConfig loadConfigFromFile(const std::string& configPath = "config.ini");

} // namespace OpenEarthGenomes
