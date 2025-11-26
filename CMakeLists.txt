cmake_minimum_required(VERSION 3.15)
project(OpenEarthGenomes)

# Modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type beállítása debug információkkal
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)

endif()

# Compiler flags
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Forrás fájlok
set(SOURCES
    src/main.cpp
    src/DatabaseManager.cpp
    src/GenomeLoader.cpp
)

# Executable létrehozása
add_executable(GenomeDatabase ${SOURCES})

# Include könyvtárak
target_include_directories(GenomeDatabase PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

# MySQL Connector/C++ keresése és linkelése
if(WIN32)
    # Windows környezet
    message(STATUS "Configuring for Windows...")
    
    # MySQL Connector/C++ keresése több helyen
    set(MYSQL_SEARCH_PATHS
        "C:/Program Files/MySQL/Connector C++ 8.0"
        "C:/Program Files/MySQL/MySQL Connector C++ 8.0"
        "C:/mysql-connector-c++-8.0.37-winx64"
        "$ENV{MYSQL_CONNECTOR_ROOT}"
    )


    find_path(MYSQL_CONNECTOR_INCLUDE_DIR
        NAMES mysqlx/xdevapi.h
        PATHS ${MYSQL_SEARCH_PATHS}
        PATH_SUFFIXES include
        DOC "MySQL Connector/C++ include directory"
    )
    
    find_library(MYSQL_CONNECTOR_LIB
        NAMES mysqlcppconn8 mysqlcppconn8-static
        PATHS ${MYSQL_SEARCH_PATHS}
        PATH_SUFFIXES lib64/vs14 lib lib64
        DOC "MySQL Connector/C++ library"
    )
    
    if(MYSQL_CONNECTOR_INCLUDE_DIR AND MYSQL_CONNECTOR_LIB)
        message(STATUS "Found MySQL Connector/C++:")
        message(STATUS "  Include: ${MYSQL_CONNECTOR_INCLUDE_DIR}")
        message(STATUS "  Library: ${MYSQL_CONNECTOR_LIB}")
        
        target_include_directories(GenomeDatabase PRIVATE ${MYSQL_CONNECTOR_INCLUDE_DIR})
        target_link_libraries(GenomeDatabase PRIVATE ${MYSQL_CONNECTOR_LIB})
        
        # Windows specifikus linkek
        target_link_libraries(GenomeDatabase PRIVATE ws2_32 crypt32 bcrypt)
        
    else()
        message(FATAL_ERROR "MySQL Connector/C++ not found! Please install it and set MYSQL_CONNECTOR_ROOT")
    endif()

    else()
    # Linux/Unix környezet
    message(STATUS "Configuring for Linux/Unix...")
    
    # pkg-config használata
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(MYSQLCPPCONN mysqlcppconn8)
        if(MYSQLCPPCONN_FOUND)
            target_include_directories(GenomeDatabase PRIVATE ${MYSQLCPPCONN_INCLUDE_DIRS})
            target_link_libraries(GenomeDatabase PRIVATE ${MYSQLCPPCONN_LIBRARIES})
            target_compile_options(GenomeDatabase PRIVATE ${MYSQLCPPCONN_CFLAGS_OTHER})
        endif()
    endif()
    
    # Ha pkg-config nem talált semmit, próbáljuk find_library-vel
    if(NOT MYSQLCPPCONN_FOUND)
        find_library(MYSQLCPPCONN_LIB 
            NAMES mysqlcppconn8 mysqlcppconn
            PATHS /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu
        )
        
        find_path(MYSQLCPPCONN_INCLUDE 
            NAMES mysqlx/xdevapi.h
            PATHS /usr/include /usr/local/include /usr/include/mysql-cppconn-8
        )
        
        if(MYSQLCPPCONN_LIB AND MYSQLCPPCONN_INCLUDE)
            message(STATUS "Found MySQL Connector/C++ via find_library:")
            message(STATUS "  Include: ${MYSQLCPPCONN_INCLUDE}")
            message(STATUS "  Library: ${MYSQLCPPCONN_LIB}")
            
            target_include_directories(GenomeDatabase PRIVATE ${MYSQLCPPCONN_INCLUDE})
            target_link_libraries(GenomeDatabase PRIVATE ${MYSQLCPPCONN_LIB})
        else()
            message(FATAL_ERROR "MySQL Connector/C++ not found! Install with: sudo apt-get install libmysqlcppconn-dev")
        endif()
    endif()
endif()

# INI parser hozzáadása (ha van libs/inih mappa)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/inih/ini.c")
    message(STATUS "Adding INI parser from libs/inih")
    target_sources(GenomeDatabase PRIVATE libs/inih/ini.c)
    target_include_directories(GenomeDatabase PRIVATE libs/inih)
    target_compile_definitions(GenomeDatabase PRIVATE INI_ALLOW_MULTILINE=1)
endif()

# Debug információk
message(STATUS "Build configuration:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")

# Install rules
install(TARGETS GenomeDatabase
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
