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

# Platform-specifikus MySQL beállítás
if(WIN32)
    # Windows: manuális elérési út vagy vcpkg
    if(DEFINED ENV{MYSQL_CONNECTOR_PATH})
        set(MYSQL_ROOT $ENV{MYSQL_CONNECTOR_PATH})
    else()
        # vcpkg esetén automatikus
        find_package(MySQL REQUIRED)
    endif()
    
    find_path(MYSQL_INCLUDE_DIR mysql/jdbc.h PATHS "${MYSQL_ROOT}/include")
    find_library(MYSQL_LIB NAMES mysqlcppconn8 PATHS "${MYSQL_ROOT}/lib")
    
    if(MYSQL_INCLUDE_DIR AND MYSQL_LIB)
        target_include_directories(GenomeDatabase PRIVATE ${MYSQL_INCLUDE_DIR})
        target_link_libraries(GenomeDatabase PRIVATE ${MYSQL_LIB})
    else()
        message(FATAL_ERROR "MySQL Connector not found on Windows!")
    endif()
else()
    # Linux: pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(MYSQLCPPCONN REQUIRED mysqlcppconn8)
    target_link_libraries(GenomeDatabase PRIVATE ${MYSQLCPPCONN_LIBRARIES})
    target_include_directories(GenomeDatabase PRIVATE ${MYSQLCPPCONN_INCLUDE_DIRS})
endif()
