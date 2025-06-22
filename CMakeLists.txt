cmake_minimum_required(VERSION 3.10)
project(OpenEarthGenomes)

# MySQL Connector beállítása
find_package(MySQL REQUIRED)

# Forrásfájlok
add_executable(GenomeDatabase
    src/main.cpp
    src/DatabaseManager.cpp
    src/GenomeLoader.cpp
)

# Könyvtárak linkelése
target_include_directories(GenomeDatabase PRIVATE ${MYSQL_INCLUDE_DIR})
target_link_libraries(GenomeDatabase PRIVATE ${MYSQL_LIBRARY})
# Include mappák hozzáadása
include_directories(src/)
