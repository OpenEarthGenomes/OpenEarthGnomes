#pragma once

#include "DatabaseManager.h"
#include <string>
#include <vector>
#include <fstream>

namespace OpenEarthGenomes {

struct FASTASequence {
    std::string header;
    std::string sequence;
    std::string species_name;
    std::string common_name;
};

class GenomeLoader {
public:
    GenomeLoader(DatabaseManager& db);
    
    // FASTA fájl betöltése
    bool loadFASTAFile(const std::string& filePath);
    
    // Batch betöltés több fájlból
    bool loadFromDirectory(const std::string& directoryPath);
    
    // Statisztikák
    size_t getLoadedSequences() const;
    size_t getTotalBasePairs() const;
    
    // Hibakezelés
    std::string getLastError() const;
    
    // Beállítások
    void setMaxSequenceLength(size_t maxLength);
    void setVerbose(bool verbose);

private:
    DatabaseManager& m_database;
    size_t m_loadedSequences;
    size_t m_totalBasePairs;
    size_t m_maxSequenceLength;
    bool m_verbose;
    std::string m_lastError;
    
    // Segéd függvények
    std::vector<FASTASequence> parseFASTAFile(const std::string& filePath);
    void extractSpeciesInfo(FASTASequence& seq);
    bool validateSequence(const std::string& sequence);
    void setLastError(const std::string& error);
};

} // namespace OpenEarthGenomes
