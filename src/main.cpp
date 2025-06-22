#include "database.h"
int main() {
  Database db;
  db.load_from_file("../database/sample.fa");
  auto results = db.find_species("gnome");
  // Eredmények megjelenítése
}
