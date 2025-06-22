#include "database.h"
int main() {
  Database db;
  db.load_from_file("../database/sample.fa");
  auto results = db.find_species("gnome");
  // Eredmények megjelenítése
}#include "database.h"
#include <iostream>

int main() {
    Database db("genomes.db");
    
    // Tábla létrehozása (ha még nem létezik)
    db.execute(R"(
        CREATE TABLE IF NOT EXISTS genomes (
            id INTEGER PRIMARY KEY,
            species TEXT NOT NULL,
            sequence TEXT NOT NULL
        );
    )");
    
    std::cout << "Adatbázis inicializálva!" << std::endl;
    return 0;
}#include "database.h"
int main() {
  Database db;
  db.load_from_file("../database/sample.fa");
  auto results = db.find_species("gnome");
  // Eredmények megjelenítése
}
