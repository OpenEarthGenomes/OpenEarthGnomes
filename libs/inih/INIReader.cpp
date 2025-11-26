#include "INIReader.h"
#include <fstream>
#include <algorithm>
#include <cctype>

INIReader::INIReader(const std::string& filename) : _error(0) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        _error = -1;
        return;
    }

    std::string line;
    std::string current_section;
    
    while (std::getline(file, line)) {
        // Üres sorok és kommentek kihagyása
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty() || line[0] == ';' || line[0] == '#')
            continue;

        // Section
        if (line[0] == '[' && line[line.length()-1] == ']') {
            current_section = line.substr(1, line.length()-2);
            continue;
        }

        // Key=value párok
        size_t equals_pos = line.find('=');
        if (equals_pos != std::string::npos) {
            std::string key = line.substr(0, equals_pos);
            std::string value = line.substr(equals_pos + 1);
            _values[current_section][key] = value;
        }
    }
}

int INIReader::ParseError() const {
    return _error;
}

std::string INIReader::Get(const std::string& section, const std::string& name, const std::string& default_value) const {
    auto sec_it = _values.find(section);
    if (sec_it == _values.end())
        return default_value;

    auto key_it = sec_it->second.find(name);
    if (key_it == sec_it->second.end())
        return default_value;

    return key_it->second;
}
