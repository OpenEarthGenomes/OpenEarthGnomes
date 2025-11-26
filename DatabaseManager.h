#pragma once
#include <string>
#include <mysql/jdbc.h>

class DatabaseManager {
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* connection;
    
public:
    DatabaseManager(const std::string& host, const std::string& user, 
                   const std::string& password, const std::string& database);
    ~DatabaseManager();
    
    bool uploadGenome(const std::string& common_name, const std::string& scientific_name, 
                     const std::string& genome_data);
    std::string downloadGenome(const std::string& scientific_name);
};
