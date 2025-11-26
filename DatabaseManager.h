#include "DatabaseManager.h"
#include <iostream>
#include <stdexcept>

DatabaseManager::DatabaseManager(const std::string& host, const std::string& user, 
                               const std::string& password, const std::string& database) {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        connection = driver->connect("tcp://" + host + ":3306", user, password);
        connection->setSchema(database);
        std::cout << "✅ MySQL database connected successfully!" << std::endl;
    } catch (sql::SQLException& e) {
        std::cerr << "❌ MySQL Error: " << e.what() << std::endl;
        throw std::runtime_error("Database connection failed");
    }
}

DatabaseManager::~DatabaseManager() {
    delete connection;
}

bool DatabaseManager::uploadGenome(const std::string& common_name, const std::string& scientific_name, 
                                 const std::string& genome_data) {
    try {
        sql::PreparedStatement* stmt = connection->prepareStatement(
            "INSERT INTO genomes (common_name, scientific_name, sequence) VALUES (?, ?, ?)"
        );
        stmt->setString(1, common_name);
        stmt->setString(2, scientific_name);
        stmt->setString(3, genome_data);
        stmt->execute();
        delete stmt;
        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "❌ Upload error: " << e.what() << std::endl;
        return false;
    }
}

std::string DatabaseManager::downloadGenome(const std::string& scientific_name) {
    try {
        sql::PreparedStatement* stmt = connection->prepareStatement(
            "SELECT sequence FROM genomes WHERE scientific_name = ?"
        );
        stmt->setString(1, scientific_name);
        sql::ResultSet* res = stmt->executeQuery();
        
        std::string result;
        if (res->next()) {
            result = res->getString("sequence");
        }
        
        delete res;
        delete stmt;
        return result;
    } catch (sql::SQLException& e) {
        std::cerr << "❌ Download error: " << e.what() << std::endl;
        return "";
    }
}
