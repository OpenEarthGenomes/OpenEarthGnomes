  #include "GenomeLoader.h"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <regex>

namespace fs = std::filesystem;

namespace OpenEarthGenomes {

GenomeLoader::GenomeLoader(DatabaseManager& db)
    : m_database(db), m_loadedSequences(0), m_totalBasePairs(0),
      m_maxSequenceLength(1000000000), // 1GB max default
      m_verbose(true) {
}

bool GenomeLoader::loadFASTAFile(const std::string& filePath) {
    if (m_verbose) {
        std::cout << "FASTA fájl betöltése: " << filePath << std::endl;
    }
    
    // Fájl létezésének ellenőrzése
    if (!fs::exists(filePath)) {
        setLastError("A fájl nem található: " + filePath);
        return false;
    }
    
    try {
        // FASTA fájl parsing
        auto sequences = parseFASTAFile(filePath);
        
        if (sequences.empty()) {
            setLastError("Nem találhatók érvényes szekvenciák a fájlban");
            return false;
        }
        
        // Szekvenciák beszúrása az adatbázisba
        size_t successful = 0;
        for (const auto& seq : sequences) {
            GenomeRecord genome;
            genome.species_name = seq.species_name;
            genome.common_name = seq.common_name;
            genome.sequence = seq.sequence;
            genome.file_source = filePath;
            genome.sequence_length = seq.sequence.length();
            
            if (m_database.insertGenome(genome)) {
                successful++;
                m_loadedSequences++;
                m_totalBasePairs += genome.sequence_length;
            }
        }

        if (m_verbose) {
            std::cout << "Betöltve: " << successful << "/" << sequences.size() 
                      << " szekvencia" << std::endl;
        }
        
        return successful > 0;
        
    } catch (const std::exception& e) {
        setLastError("Fájl betöltési hiba: " + std::string(e.what()));
        return false;
    }
}

bool GenomeLoader::loadFromDirectory(const std::string& directoryPath) {
    if (m_verbose) {
        std::cout << "Könyvtár szkennelése: " << directoryPath << std::endl;
    }
    
    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
        setLastError("A könyvtár nem található: " + directoryPath);
        return false;
    }
    
    bool anySuccess = false;
    size_t fileCount = 0;
    
    try {
        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();

std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
                
                // FASTA fájl kiterjesztések
                if (ext == ".fasta" || ext == ".fa" || ext == ".fas" || 
                    ext == ".fna" || ext == ".ffn" || ext == ".faa") {
                    
                    fileCount++;
                    if (loadFASTAFile(entry.path().string())) {
                        anySuccess = true;
                    }
                }
            }
        }
        
        if (m_verbose) {
            std::cout << "Összesen " << fileCount << " FASTA fájl feldolgozva" << std::endl;
        }
        
    } catch (const std::exception& e) {
        setLastError("Könyvtár olvasási hiba: " + std::string(e.what()));
        return false;
    }
    
    return anySuccess;
}

std::vector<FASTASequence> GenomeLoader::parseFASTAFile(const std::string& filePath) {
    std::vector<FASTASequence> sequences;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Nem sikerült megnyitni a fájlt");
    }
    
    FASTASequence currentSeq;
    std::string line;
    
    while (std::getline(file, line)) {
// Üres sorok kihagyása
        if (line.empty()) {
            continue;
        }
        
        if (line[0] == '>') {
            // Új szekvencia kezdődik
            if (!currentSeq.sequence.empty()) {
                // Előző szekvencia mentése
                if (validateSequence(currentSeq.sequence)) {
                    extractSpeciesInfo(currentSeq);
                    sequences.push_back(currentSeq);
                }
            }
            
            // Új szekvencia inicializálása
            currentSeq = FASTASequence();
            currentSeq.header = line.substr(1); // '>' karakter elhagyása
            
        } else {
            // Szekvencia adat hozzáadása
            std::string cleanLine = line;
            // Whitespace karakterek eltávolítása
            cleanLine.erase(std::remove_if(cleanLine.begin(), cleanLine.end(), ::isspace), cleanLine.end());
            
            currentSeq.sequence += cleanLine;

           // Méret ellenőrzése
            if (currentSeq.sequence.length() > m_maxSequenceLength) {
                if (m_verbose) {
                    std::cout << "Figyelmeztetés: Szekvencia túl hosszú, csonkítva: " 
                              << currentSeq.header << std::endl;
                }
                currentSeq.sequence = currentSeq.sequence.substr(0, m_maxSequenceLength);
                break;
            }
        }
    }
    
    // Utolsó szekvencia hozzáadása
    if (!currentSeq.sequence.empty() && validateSequence(currentSeq.sequence)) {
        extractSpeciesInfo(currentSeq);
        sequences.push_back(currentSeq);
    }
    
    return sequences;
}

void GenomeLoader::extractSpeciesInfo(FASTASequence& seq) {
    // Faj név kinyerése a header-ből
    std::string header = seq.header;
    
    // Gyakori minták keresése
    std::regex species_pattern(R"(\b([A-Z][a-z]+\s+[a-z]+)\b)");
    std::smatch matches;
    
    if (std::regex_search(header, matches, species_pattern)) {
        seq.species_name = matches[1].str();
    } else {
        // Ha nem található, használjuk a header első részét
        size_t spacePos = header.find(' ');
        if (spacePos != std::string::npos) {
            seq.species_name = header.substr(0, spacePos);
        } else {
            seq.species_name = header;
        }
    }

    // Common name kinyerése (ha van zárójelben)
    std::regex common_pattern(R"(\(([^)]+)\))");
    if (std::regex_search(header, matches, common_pattern)) {
        seq.common_name = matches[1].str();
    }
    
    // Ha nincs species name, próbáljunk valami értelmes nevet
    if (seq.species_name.empty()) {
        seq.species_name = "Unknown_species";
    }
}

bool GenomeLoader::validateSequence(const std::string& sequence) {
    if (sequence.empty()) {
        return false;
    }
    
    // Csak érvényes nukleotidok: A, T, G, C, N (és kis betűk)
    for (char c : sequence) {
        char upper_c = std::toupper(c);
        if (upper_c != 'A' && upper_c != 'T' && upper_c != 'G' && 
            upper_c != 'C' && upper_c != 'N') {
            if (m_verbose) {
                std::cout << "Figyelmeztetés: Érvénytelen karakter a szekvenciában: " << c << std::endl;
            }
            // Megengedő validálás - ne dobjuk ki az egész szekvenciát egy rossz karakter miatt
        }
    }
    
    return true;
}

size_t GenomeLoader::getLoadedSequences() const {
    return m_loadedSequences;
}

size_t GenomeLoader::getTotalBasePairs() const {
    return m_totalBasePairs;
}

std::string GenomeLoader::getLastError() const {
    return m_lastError;
}

void GenomeLoader::setMaxSequenceLength(size_t maxLength) {
    m_maxSequenceLength = maxLength;
}

void GenomeLoader::setVerbose(bool verbose) {
    m_verbose = verbose;
}

void GenomeLoader::setLastError(const std::string& error) {
    m_lastError = error;
}

} // namespace OpenEarthGenomes
