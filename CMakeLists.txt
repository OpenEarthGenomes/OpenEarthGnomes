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
