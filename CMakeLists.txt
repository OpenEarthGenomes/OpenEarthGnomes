cmake_minimum_required(VERSION 3.12)
project(OpenEarthGenomes VERSION 1.0.0 LANGUAGES CXX)

# C++ beállítások
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fordítási beállítások
if(MSVC)
    # Visual Studio
    add_compile_options(/W4 /permissive-)
else()
    # GCC/Clang
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Forrásfájlok automatikus keresése
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Fő program
add_executable(GenomeDatabase ${SOURCES} ${HEADERS})

# Include mappák
target_include_directories(GenomeDatabase PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# C++17 fájlrendszer támogatás
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(GenomeDatabase PRIVATE stdc++fs)
endif()

# Windows specific settings
if(WIN32)
    target_compile_definitions(GenomeDatabase PRIVATE _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
endif()

# Installálás beállítása
install(TARGETS GenomeDatabase
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION bin
)

# Tesztelés beállítása (opcionális)
enable_testing()

# Package info
set(CPACK_PACKAGE_NAME "OpenEarthGenomes")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include(CPack)
