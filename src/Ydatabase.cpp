// database.h
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
