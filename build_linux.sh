#!/bin/bash
set -e  # Kilépés hibánál

# Színek a kimenethez
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Logo és információ
echo -e "${BLUE}"
echo "   ___                      _   _   _      "
echo "  / _ \ _ __   ___ _ __    /_\ | |_| |__   ___ _ __ ___ "
echo " | | | | '_ \ / _ \ '_ \  //_\\| __| '_ \ / _ \ '__/ _ \\"
echo " | |_| | |_) |  __/ | | |/  _  \ |_| | | |  __/ | |  __/"
echo "  \___/| .__/ \___|_| |_|_/ \_|\__|_| |_|\___|_|  \___|"
echo "       |_|                                             "
echo -e "${NC}"
echo -e "${YELLOW}OpenEarthGnomes Build Script${NC}"
echo "======================================"

# Funkció: hiba esetén kilépés
error_exit() {
    echo -e "${RED}❌ Hiba: $1${NC}" >&2
    exit 1
}

# Funkció: információ kiírása
info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

# Funkció: siker kiírása
success() {
    echo -e "${GREEN}✅ $1${NC}"
}

# Funkció: figyelmeztetés kiírása
warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

# 1. Rendszer információk
info "Rendszer információk:"
echo "    OS: $(lsb_release -d | cut -f2)"
echo "    Arch: $(uname -m)"
echo "    CPU magok: $(nproc)"
echo "    Memória: $(free -h | awk '/^Mem:/ {print $2}')"

# 2. Függőségek ellenőrzése és telepítése
info "Függőségek ellenőrzése..."

REQUIRED_PACKAGES=(
    "cmake"
    "g++"
    "libmysqlcppconn8-dev"
    "pkg-config"
    "build-essential"
    "libssl-dev"
)

MISSING_PACKAGES=()

for package in "${REQUIRED_PACKAGES[@]}"; do
    if ! dpkg -l | grep -q " $package "; then
        MISSING_PACKAGES+=("$package")
    fi
done

if [ ${#MISSING_PACKAGES[@]} -ne 0 ]; then
    warning "Hiányzó csomagok: ${MISSING_PACKAGES[*]}"
    info "Függőségek telepítése..."
    
    sudo apt-get update || error_exit "APT update sikertelen"
    sudo apt-get install -y "${MISSING_PACKAGES[@]}" || error_exit "Csomagok telepítése sikertelen"
    
    success "Függőségek telepítve"
else
    success "Minden függőség telepítve"
fi

# 3. Build könyvtár előkészítése
info "Build környezet előkészítése..."

if [ -d "build" ]; then
    warning "Régi build könyvtár törlése..."
    rm -rf build || error_exit "Régi build könyvtár törlése sikertelen"
fi

mkdir -p build || error_exit "Build könyvtár létrehozása sikertelen"
cd build || error_exit "Build könyvtárba navigálás sikertelen"

# 4. CMake konfiguráció
info "CMake konfigurálás..."

# Build típus beállítása (ha nincs megadva, akkor Release)
BUILD_TYPE=${1:-Release}

cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE || error_exit "CMake konfiguráció sikertelen"

success "CMake konfiguráció sikeres"

# 5. Fordítás
info "Fordítás elindítva ($BUILD_TYPE módban)..."

CPU_CORES=$(nproc)
info "Használt CPU magok: $CPU_CORES"

make -j$CPU_CORES || error_exit "Fordítás sikertelen"

success "Fordítás sikeres"

# 6. Eredmények ellenőrzése
info "Build eredmények ellenőrzése..."

if [ -f "GenomeDatabase" ]; then
    success "Bináris fájl létrehozva: $(pwd)/GenomeDatabase"
    
    # Bináris információ
    echo ""
    info "Bináris információ:"
    file GenomeDatabase
    echo "    Méret: $(du -h GenomeDatabase | cut -f1)"
    
    # Próbáljuk futtatni a help opciót
    info "Teszt futtatása..."
    if ./GenomeDatabase --help > /dev/null 2>&1; then
        success "A program sikeresen fut"
    elif ./GenomeDatabase --version > /dev/null 2>&1; then
        success "A program sikeresen fut (verzió információ)"
    else
        warning "A program nem támogatja a --help/--version opciókat, de bináris formátuma helyes"
    fi
    
else
    error_exit "A bináris fájl nem jött létre"
fi

# 7. Végső összefoglaló
echo ""
echo -e "${GREEN}======================================${NC}"
success "🎉 BUILD SIKERES!"
echo ""
info "Használd a programot:"
echo "  ./build/GenomeDatabase"
echo ""
info "Build típus: $BUILD_TYPE"
info "Bináris helye: $(pwd)/GenomeDatabase"
info "Build idő: $(date)"
echo -e "${GREEN}======================================${NC}"

# 8. További lehetőségek
echo ""
info "További lehetőségek:"
echo "  Debug build készítése: ./build_linux.sh Debug"
echo "  Build törlése: rm -rf build"
echo "  Program futtatása: ./build/GenomeDatabase"
