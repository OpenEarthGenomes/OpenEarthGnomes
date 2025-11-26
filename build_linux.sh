#!/bin/bash

echo "OpenEarthGenomes - Linux Build Script"
echo "===================================="

# Szükséges csomagok ellenőrzése
check_package() {
    if ! dpkg -l | grep -q "^ii  $1 "; then
        echo "HIÁNYZÓ CSOMAG: $1"
        echo "Telepítés: sudo apt-get install $1"
        return 1
    fi
    return 0
}

echo "Függőségek ellenőrzése..."
missing_packages=0

for pkg in cmake g++ libmysqlcppconn-dev pkg-config; do
    if ! check_package $pkg; then
        missing_packages=$((missing_packages + 1))
    fi
done

if [ $missing_packages -gt 0 ]; then
    echo ""
    echo "HIÁNYZÓ FÜGGŐSÉGEK! Telepítsd az alábbi paranccsal:"
    echo "sudo apt-get update"
    echo "sudo apt-get install cmake g++ libmysqlcppconn-dev pkg-config"
    exit 1
fi

# MySQL szerver ellenőrzése
if ! systemctl is-active --quiet mysql; then
    echo ""
    echo "FIGYELEM: MySQL szerver nem fut!"
    echo "Indítsd el: sudo systemctl start mysql"
    echo "Auto-start: sudo systemctl enable mysql"
fi

# Build könyvtár létrehozása
echo ""
echo "Build könyvtár előkészítése..."
rm -rf build
mkdir -p build
cd build

# CMake konfiguráció
echo "CMake konfigurálása..."
cmake .. -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo "HIBA: CMake konfiguráció sikertelen!"
    exit 1
fi

# Fordítás
echo ""
echo "Projekt fordítása..."
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo "HIBA: Fordítás sikertelen!"
    exit 1
fi

# Eredmény ellenőrzése
if [ -f "GenomeDatabase" ]; then
    echo ""
    echo "================================="
    echo "SIKERES FORDÍTÁS!"
    echo "================================="
    echo "Executable: build/GenomeDatabase"
    echo ""
    echo "Használat:"
    echo "  cd build"
    echo "  ./GenomeDatabase --help"
    echo ""
    echo "Adatbázis inicializálása:"
    echo "  mysql -u root -p < ../setup.sql"
    echo "  ./GenomeDatabase --init"
    echo ""
else
    echo "HIBA: Az executable nem jött létre!"
    exit 1
fi
