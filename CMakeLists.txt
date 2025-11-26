cmake_minimum_required(VERSION 3.10)
project(OpenEarthGenomes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Forrásfájlok
set(SOURCES
    src/main.cpp
    src/DatabaseManager.cpp
    src/GenomeLoader.cpp
)

add_executable(GenomeDatabase ${SOURCES})

# Include mappák
target_include_directories(GenomeDatabase PRIVATE src/)

# MySQL linkelés - egyszerű verzió
if(WIN32)
    # Windows: keressük a MySQL könyvtárakat
    find_library(MYSQLCPP_LIB NAMES mysqlcppconn8 PATHS "C:/Program Files/MySQL/*")
    find_library(MYSQL_LIB NAMES mysqlclient PATHS "C:/Program Files/MySQL/*")
    
    if(MYSQLCPP_LIB AND MYSQL_LIB)
        target_link_libraries(GenomeDatabase PRIVATE ${MYSQLCPP_LIB} ${MYSQL_LIB})
    else()
        message(WARNING "MySQL libraries not found, build may fail")
    endif()
else()
    # Linux: pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(MYSQLCPPCONN REQUIRED mysqlcppconn8)
    target_link_libraries(GenomeDatabase PRIVATE ${MYSQLCPPCONN_LIBRARIES})
endif()
