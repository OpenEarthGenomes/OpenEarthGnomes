// DatabaseManager.cpp
#include "DatabaseManager.h"
#include <fstream>
#include <inih/INIReader.h> // INI parser hozzáadása

DatabaseManager::DatabaseManager() {
    // Konfig fájl olvasása
    INIReader reader("config.ini");
    
    if (reader.ParseError() < 0) {
        throw std::runtime_error("Nem található config.ini fájl!");
    }

    std::string host = reader.Get("database", "host", "localhost");
    std::string user = reader.Get("database", "user", "root");
    std::string password = reader.Get("database", "password", "");
    std::string database = reader.Get("database", "database", "EarthGenomes");

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://" + host + ":3306", user, password);
    con->setSchema(database);
}#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& host, const std::string& user, 
                               const std::string& password, const std::string& database) {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://" + host + ":3306", user, password);
    con->setSchema(database);
}

DatabaseManager::~DatabaseManager() {
    delete con;
}

void DatabaseManager::uploadGenome(const std::string& commonName, 
                                 const std::string& scientificName, 
                                 const std::string& genomeData) {
    sql::PreparedStatement* pstmt = con->prepareStatement(
        "INSERT INTO Species (common_name, scientific_name, genome) VALUES (?, ?, ?)"
    );
    pstmt->setString(1, commonName);
    pstmt->setString(2, scientificName);
    pstmt->setString(3, genomeData);
    pstmt->execute();
    delete pstmt;
}

std::string DatabaseManager::downloadGenome(const std::string& scientificName) {
    sql::PreparedStatement* pstmt = con->prepareStatement(
        "SELECT genome FROM Species WHERE scientific_name = ?"
    );
    pstmt->setString(1, scientificName);
    sql::ResultSet* res = pstmt->executeQuery();
    
    if (!res->next()) {
        delete res;
        delete pstmt;
        throw std::runtime_error("Nincs ilyen genom: " + scientificName);
    }
    
    std::string genome = res->getString("genome");
    delete res;
    delete pstmt;
    return genome;
}
