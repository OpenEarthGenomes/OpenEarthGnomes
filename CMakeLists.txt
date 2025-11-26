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

# Fő program létrehozása - CSAK EGYSZER!
add_executable(GenomeDatabase ${SOURCES})

# Include mappák
target_include_directories(GenomeDatabase PRIVATE 
    src/
    libs/inih
)

# Egyszerű build MySQL nélkül
if(WIN32)
    message(STATUS "Windows build - skipping MySQL for now")
    # Windows-on linkeljünk alap könyvtárakat
    target_link_libraries(GenomeDatabase)
else()
    # Linux-on próbáljuk meg a MySQL-t
    find_package(PkgConfig)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(MYSQLCPPCONN mysqlcppconn8)
        if(MYSQLCPPCONN_FOUND)
            target_link_libraries(GenomeDatabase PRIVATE ${MYSQLCPPCONN_LIBRARIES})
            target_include_directories(GenomeDatabase PRIVATE ${MYSQLCPPCONN_INCLUDE_DIRS})
        endif()
    endif()
endif()
