#include "database.h"
#include <iostream>

Database::Database(const std::string& path) {
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Adatbázis hiba: " << sqlite3_errmsg(db) << std::endl;
    }
}

Database::~Database() {
    if (db) sqlite3_close(db);
}

bool Database::execute(const std::string& sql) {
    char* error = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error) != SQLITE_OK) {
        std::cerr << "SQL hiba: " << error << std::endl;
        sqlite3_free(error);
        return false;
    }
    return true;
}// database.h
#pragma once
#include <vector>
#include <string>

struct Genome {
  std::string species;
  std::string sequence;
};

class Database {
public:
  void load_from_file(const std::string& path);
  std::vector<Genome> find_species(const std::string& name);
private:
  std::vector<Genome> genomes;
};
