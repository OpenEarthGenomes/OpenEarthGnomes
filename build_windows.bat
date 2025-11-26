@echo off
echo OpenEarthGenomes - Windows Build Script
echo =====================================

REM Ellenőrizzük, hogy létezik-e a Visual Studio
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo HIBA: CMake nem található a PATH-ban!
    echo Telepítsd a Visual Studio 2022-t a "Desktop development with C++" workload-dal.
    pause
    exit /b 1
)

REM MySQL Connector/C++ ellenőrzése
set MYSQL_CONNECTOR_ROOT=C:\mysql-connector-c++-8.0.37-winx64
if not exist "%MYSQL_CONNECTOR_ROOT%" (
    echo HIBA: MySQL Connector/C++ nem található!
    echo Töltsd le és csomagold ki ide: %MYSQL_CONNECTOR_ROOT%
    echo Letöltés: https://dev.mysql.com/downloads/connector-cpp/
    pause
    exit /b 1
)

REM Build könyvtár létrehozása
if exist build rmdir /s /q build
mkdir build
cd build

echo.
echo CMake konfigurálása...
cmake .. -DCMAKE_BUILD_TYPE=Release -DMYSQL_CONNECTOR_ROOT=%MYSQL_CONNECTOR_ROOT%

if %ERRORLEVEL% NEQ 0 (
    echo HIBA: CMake konfiguráció sikertelen!
    pause
    exit /b 1
)

echo.
echo Projekt fordítása...
cmake --build . --config Release

if %ERRORLEVEL% NEQ 0 (
    echo HIBA: Fordítás sikertelen!
    pause
    exit /b 1
)

echo.
echo DLL fájlok másolása...
copy "%MYSQL_CONNECTOR_ROOT%\lib64\vs14\mysqlcppconn8.dll" Release\ >nul 2>nul

if exist Release\GenomeDatabase.exe (
    echo.
    echo ===================================
    echo SIKERES FORDÍTÁS!
    echo ===================================
    echo Executable: build\Release\GenomeDatabase.exe
    echo.
    echo Használat:
    echo   cd build\Release
    echo   GenomeDatabase.exe --help
    echo.
) else (
    echo HIBA: Az executable nem jött létre!
)

pause
