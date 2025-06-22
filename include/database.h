#pragma once
#include <sqlite3.h>
#include <string>

class Database {
public:
    Database(const std::string& path);
    ~Database();
    bool execute(const std::string& sql);
    
private:
    sqlite3* db = nullptr;
};#pragma once
#include <sqlite3.h>
#include <string>

class Database {
public:
    Database(const std::string& path);
    ~Database();
    
    bool execute(const std::string& sql); // SQL parancs végrehajtása
    
private:
    sqlite3* db = nullptr;
};
