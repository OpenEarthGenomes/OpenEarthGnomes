cmake_minimum_required(VERSION 3.10)

# Projekt neve (NE legyen benne 'if'!)
project(DatabaseApp)

# Windows-specifikus beállítások
if(WIN32)
    # MySQL elérési útjának megadása Windows-on
    set(MYSQL_DIR "C:/Program Files/MySQL/MySQL Server 8.0")  # Módosítsd a saját elérési utadra!
    set(CMAKE_PREFIX_PATH "${MYSQL_DIR}/lib")
    
    # DLL-ek másolása a build mappába
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${MYSQL_DIR}/lib/libmysql.dll"
            $<TARGET_FILE_DIR:app>
    )
endif()

# Forrásfájlok hozzáadása
add_executable(app 
    src/database.cpp
    src/main.cpp
)

# MySQL linkelése
find_package(MySQL REQUIRED)
target_link_libraries(app PRIVATE MySQL::MySQL)# JAVÍTVA: 
find_package(SQLite3 REQUIRED)  # Kisbetűs "SQLite3"

# SQLite linkelés javítva:
target_link_libraries(main_app PRIVATE ${SQLite3_LIBRARIES})if(WIN32)
find_package(SQLite3 REQUIRED)
set(SQLite3_LIBRARIES sqlite3)
endif()cmake_minimum_required(VERSION 3.10)
project(OpenEarthGnomes)

# SQLite keresése
find_package(SQLite3 REQUIRED)

# Fejlécmappa beállítása
include_directories(
    include
    ${SQLite3_INCLUDE_DIRS}  # SQLite fejlécek hozzáadása
)

# Forrásfájlok összegyűjtése
file(GLOB SOURCES "src/*.cpp")

# Fő program létrehozása
add_executable(main_app ${SOURCES})

# SQLite linkelése
target_link_libraries(main_app PRIVATE SQLite::SQLite3)

# Teszt rész
enable_testing()
add_subdirectory(tests)cmake_minimum_required(VERSION 3.10)
project(OpenEarthGnomes)

# KIJAVÍTVA:
include_directories(include)  # Header mappa hozzáadva
add_subdirectory(src)         # Forráskód hozzáadva

# Tesztkereső beállítás
enable_testing()
add_subdirectory(tests)cmake_minimum_required(VERSION 3.10)
project(OpenEarthGenomes)

# INI Parser hozzáadása
add_subdirectory(libs/inih)

# MySQL Connector beállítása
find_package(MySQL REQUIRED)

# Forrásfájlok
add_executable(GenomeDatabase
    src/main.cpp
    src/DatabaseManager.cpp
    src/GenomeLoader.cpp
)

# Könyvtárak linkelése
target_include_directories(GenomeDatabase PRIVATE 
    ${MYSQL_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/libs/inih
)

target_link_libraries(GenomeDatabase PRIVATE 
    ${MYSQL_LIBRARY}
    inih
)cmake_minimum_required(VERSION 3.10)
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
target_link_libraries(main_app PRIVATE SQLite::SQLite3)
target_include_directories(GenomeDatabase PRIVATE ${MYSQL_INCLUDE_DIR})
# Include mappák hozzáadása
include_directories(src/)
