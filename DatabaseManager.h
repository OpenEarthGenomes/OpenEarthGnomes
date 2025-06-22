#pragma once
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <stdexcept>
#include <string>

class DatabaseManager {
public:
    DatabaseManager(const std::string& host, const std::string& user, 
                   const std::string& password, const std::string& database);
    ~DatabaseManager();
    
    void uploadGenome(const std::string& commonName, 
                     const std::string& scientificName, 
                     const std::string& genomeData);
    
    std::string downloadGenome(const std::string& scientificName);

private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
};
