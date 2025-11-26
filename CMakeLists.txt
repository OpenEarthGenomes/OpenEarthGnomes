    (sequence_length)
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci
        )";

        m_session->sql(sql).execute();
        
        std::cout << "Adatbázis táblák létrehozva/ellenőrizve." << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        setLastError("Tábla létrehozási hiba: " + std::string(e.what()));
        std::cerr << "Tábla létrehozási hiba: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::insertGenome(const GenomeRecord& genome) {
    if (!m_connected) {
        setLastError("Nincs aktív adatbázis kapcsolat");
        return false;
    }

    try {
        auto sql = m_session->sql(R"(
            INSERT INTO genomes 
            (species_name, common_name, sequence, file_source, sequence_length) 
            VALUES (?, ?, ?, ?, ?)
        )");
        
        sql.bind(genome.species_name)
           .bind(genome.common_name)
           .bind(genome.sequence)
           .bind(genome.file_source)
           .bind(static_cast<int64_t>(genome.sequence_length));
           
        sql.execute();
        
        std::cout << "Genom beszúrva: " << genome.species_name << 
                     " (" << genome.sequence_length << " bp)" << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        setLastError("Beszúrási hiba: " + std::string(e.what()));
        std::cerr << "Beszúrási hiba: " << e.what() << std::endl;
        return false;
    }
}

std::vector<GenomeRecord> DatabaseManager::findBySpecies(const std::string& species_name) {
    std::vector<GenomeRecord> results;
    
    if (!m_connected) {
        setLastError("Nincs aktív adatbázis kapcsolat");
        return results;
    }

    try {
        auto sql = m_session->sql(R"(
            SELECT id, species_name, common_name, sequence, file_source, 
                   upload_date, sequence_length 
            FROM genomes 
            WHERE species_name LIKE ?
        )");
        
        auto result = sql.bind("%" + species_name + "%").execute();
        
        for (auto row : result) {
            results.push_back(resultToGenome(row));
        }
            } catch (const std::exception& e) {
        setLastError("Keresési hiba: " + std::string(e.what()));
        std::cerr << "Keresési hiba: " << e.what() << std::endl;
    }
    
    return results;
}

std::vector<GenomeRecord> DatabaseManager::findByCommonName(const std::string& common_name) {
    std::vector<GenomeRecord> results;
    
    if (!m_connected) {
        setLastError("Nincs aktív adatbázis kapcsolat");
        return results;
    }

    try {
        auto sql = m_session->sql(R"(
            SELECT id, species_name, common_name, sequence, file_source, 
                   upload_date, sequence_length 
            FROM genomes 
            WHERE common_name LIKE ?
        )");
        
        auto result = sql.bind("%" + common_name + "%").execute();
        for (auto row : result) {
            results.push_back(resultToGenome(row));
        }
        
    } catch (const std::exception& e) {
        setLastError("Keresési hiba: " + std::string(e.what()));
        std::cerr << "Keresési hiba: " << e.what() << std::endl;
    }
    
    return results;
}

std::optional<GenomeRecord> DatabaseManager::findById(int id) {
    if (!m_connected) {
        setLastError("Nincs aktív adatbázis kapcsolat");
        return std::nullopt;
    }

    try {
        auto sql = m_session->sql(R"(
            SELECT id, species_name, common_name, sequence, file_source, 
                   upload_date, sequence_length 
            FROM genomes 
            WHERE id = ?
        )");
        
        auto result = sql.bind(id).execute();
        auto row = result.fetchOne();
        
        if (row) {
            return resultToGenome(row);
        }
        
    } catch (const std::exception& e) {
        setLastError("Keresési hiba: " + std::string(e.what()));
        std::cerr << "Keresési hiba: " << e.what() << std::endl;
    }
    
    return std::nullopt;
}

size_t DatabaseManager::getGenomeCount() {
    if (!m_connected) {
        return 0;
    }
    try {
        auto result = m_session->sql("SELECT COUNT(*) FROM genomes").execute();
        auto row = result.fetchOne();
        
        if (row) {
            return row[0].get<uint64_t>();
        }
        
    } catch (const std::exception& e) {
        setLastError("Számlálási hiba: " + std::string(e.what()));
        std::cerr << "Számlálási hiba: " << e.what() << std::endl;
    }
    
    return 0;
}

std::vector<std::string> DatabaseManager::getSpeciesList() {
    std::vector<std::string> species;
    
    if (!m_connected) {
        return species;
    }

    try {
        auto result = m_session->sql(
            "SELECT DISTINCT species_name FROM genomes ORDER BY species_name"
        ).execute();
        
        for (auto row : result) {
            species.push_back(row[0].get<std::string>());
        }
        
    } catch (const std::exception& e) {
        setLastError("Fajlista hiba: " + std::string(e.what()));
        std::cerr << "Fajlista hiba: " << e.what() << std::endl;
    }
    
    return species;
}

std::string DatabaseManager::getLastError() const {
    return m_lastError;
}

void DatabaseManager::setLastError(const std::string& error) {
    m_lastError = error;
}

GenomeRecord DatabaseManager::resultToGenome(const mysqlx::Row& row) {
    GenomeRecord genome;
    
    genome.id = row[0].get<int>();
    genome.species_name = row[1].get<std::string>();
    genome.common_name = row[2].isNull() ? "" : row[2].get<std::string>();
    genome.sequence = row[3].get<std::string>();
    genome.file_source = row[4].isNull() ? "" : row[4].get<std::string>();
    genome.upload_date = row[5].isNull() ? "" : row[5].get<std::string>();
    genome.sequence_length = row[6].get<uint64_t>();

    return genome;
}

#ifdef INI_ALLOW_MULTILINE
// INI parser callback
static int config_handler(void* user, const char* section, const char* name, const char* value) {
    DatabaseConfig* config = static_cast<DatabaseConfig*>(user);
    
    if (strcmp(section, "database") == 0) {
        if (strcmp(name, "host") == 0) {
            config->host = value;
        } else if (strcmp(name, "user") == 0) {
            config->user = value;
        } else if (strcmp(name, "password") == 0) {
            config->password = value;
        } else if (strcmp(name, "database") == 0) {
            config->database = value;
        } else if (strcmp(name, "port") == 0) {
            config->port = std::atoi(value);
        }
    }
    
    return 1;
}
#endif

DatabaseConfig loadConfigFromFile(const std::string& configPath) {
    DatabaseConfig config;
    
#ifdef INI_ALLOW_MULTILINE
    if (ini_parse(configPath.c_str(), config_handler, &config) < 0) {
        std::cerr << "Nem sikerült betölteni a konfigurációt: " << configPath << std::endl;
        std::cerr << "Alapértelmezett beállítások használata." << std::endl;
    } else {
        std::cout << "Konfiguráció betöltve: " << configPath << std::endl;
    }
#else
    std::cout << "INI parser nem elérhető, alapértelmezett beállítások használata." << std::endl;
#endif
    
    return config;
}

} // namespace OpenEarthGenomes
