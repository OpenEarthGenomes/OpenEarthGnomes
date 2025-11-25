cmake_minimum_required(VERSION 3.10)
project(OpenEarthGenomes)

# C++ standard beállítása
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Forrásfájlok
set(SOURCES
    src/main.cpp
    src/DatabaseManager.cpp
    src/GenomeLoader.cpp
)

# Fő program létrehozása
add_executable(GenomeDatabase ${SOURCES})

# Include mappák
target_include_directories(GenomeDatabase PRIVATE 
    src/
    libs/inih
)

# MySQL keresése és linkelése
find_package(PkgConfig REQUIRED)
pkg_check_modules(MYSQLCPPCONN REQUIRED mysqlcppconn8)

if(MYSQLCPPCONN_FOUND)
    target_link_libraries(GenomeDatabase PRIVATE ${MYSQLCPPCONN_LIBRARIES})
    target_include_directories(GenomeDatabase PRIVATE ${MYSQLCPPCONN_INCLUDE_DIRS})
    message(STATUS "MySQL Connector found and linked")
else()
    message(FATAL_ERROR "MySQL Connector not found!")
endif()
