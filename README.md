# 🌱 OpenEarthGenomes Project  
**A Föld élőlényeinek genomtára – az élet újjáépítéséhez**  

> "Az élet információja nem tulajdon – hanem minden élőlény közös öröksége."  
> "Genetic information is not property - it's the shared heritage of all life."  

---

## 🌐 Table of Contents / Tartalomjegyzék
1. [Project Goals / Projekt célok](#-project-goals--projekt-célok)
2. [Installation / Telepítés](#-installation--telepítés)
3. [Configuration / Konfiguráció](#%EF%B8%8F-configuration--konfiguráció)
4. [Database Setup / Adatbázis beállítás](#-database-setup--adatbázis-beállítás)
5. [Sample Genomes / Példa Genomok](#-sample-genomes--példa-genomok)
6. [Contribution / Közreműködés](#-contribution--közreműködés)
7. [Philosophy / Filozófia](#-philosophy--filozófia)
8. [License / Licenc](#-license--licenc)

---

## 🎯 Project Goals / Projekt célok
### 🇬🇧 English
- Create an open genomic database of Earth's biodiversity
- Enable ecosystem restoration after catastrophic events
- Provide free access to genetic information for research and education
- Develop tools for easy genomic data management

### 🇭🇺 Magyar
- A Föld élővilágának nyílt genomadatbázisának létrehozása
- Ökoszisztémák helyreállításának lehetővé tétele katasztrófák után
- Ingyenes hozzáférés biztosítása genetikai információkhoz kutatás és oktatás számára
- Egyszerű genomadatok kezelésére szolgáló eszközök fejlesztése

---

## 💻 Installation / Telepítés
### Windows
```bash
# 1. Install Visual Studio 2022 with "Desktop development with C++"
# 2. Clone repository:
git clone https://github.com/OpenEarthGenomes/OpenEarthGnomes.git
cd OpenEarthGnomes
# 3. Create build directory:
mkdir build
cd build
# 4. Configure with CMake:
cmake .. -DCMAKE_BUILD_TYPE=Release
# 5. Build project:
cmake --build . --config Release**A Föld élőlényeinek genomtára – az élet újjáépítéséhez atomkatasztrófa után**  

> "Az élet információja nem tulajdon – hanem minden élőlény közös öröksége."  

---

## 🚀 Cél
Létrehozni egy **nyílt, ingyenes, könnyen hozzáférhető genomadatbázist**, amely:  
- Tárolja a Föld élővilágának genomjait (növények, állatok, gombák, rovarok)  
- Lehetővé teszi, hogy bárki, bármikor **hozzáférjen és visszaállítsa az ökoszisztémát**  
- **Zero restrictions** – nincs titkosítás, szerzői jog, vagy kereskedelmi korlátozás  

---

## ⚙️ Technológiai háttér
| Komponens       | Leírás                                                                 |
|-----------------|------------------------------------------------------------------------|
| **C++**         | Fő programnyelv (egyszerű, hatékony EXE)                              |
| **MySQL**       | Genomadatok tárolása (FASTA formátumban)                               |
| **CMake**       | Projekt fordítás és összeállítás                                      |
| **GitHub**      | Nyílt forráskód, közösségi részvétel                                  |

---

## 📥 Telepítés

### Windows
1. Töltsd le a legfrissebb `.exe` fájlt a [Releases](https://github.com/username/OpenEarthGenomes/releases) részlegből  
2. Indítsd el a `GenomeDatabase.exe`-t  
3. Kövesd a képernyőn megjelenő utasításokat!  

### Fordítás forráskódból (Linux/Windows)
```bash
git clone https://github.com/username/OpenEarthGenomes.git
cd OpenEarthGenomes
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
./GenomeDatabase --help
## 📜 License  
[MIT License](LICENSE) - Free to use, modify, share!

## 🖥️ Fordítás Windows alatt

**Fontos Windows alatt**: 
Másold a `libmysqlcppconn.dll` fájlt az EXE mellé:
1. A MySQL Connector `lib64\vs14` mappájából
2. Az EXE fájlt tartalmazó mappába

1. Telepítsd a **Visual Studio 2022**-t (Community verzió ingyenes)
2. A telepítőben jelöld be:
   - `Desktop development with C++`
   - `C++ CMake tools for Windows`
3. Töltsd le a [MySQL Connector/C++ 8.0.37](https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-8.0.37-winx64.zip) fájlt
4. Csomagold ki pl.: `C:\mysql-connector`
5. Indítsd el a Visual Studio-t és válaszd "Open a local folder"
6. Tallózd ki a projekt mappáját
7. Kattints a "Build" menüre → "Build All"


Linux
# 1. Install dependencies:
sudo apt install git cmake g++ libmysqlclient-dev
# 2. Clone repository:
git clone https://github.com/OpenEarthGenomes/OpenEarthGnomes.git
cd OpenEarthGnomes
# 3. Create build directory:
mkdir build
cd build
# 4. Configure with CMake:
cmake .. -DCMAKE_BUILD_TYPE=Release
# 5. Build project:
make -j4


C8onfigini
[database]
host = localhost     # MySQL szerver címe
user = root          # MySQL felhasználónév
password =           # MySQL jelszó
database = EarthGenomes  # Adatbázis neve


Install MySql server
[paths]
genomes = ./genomes  # Genomfájlok helye8

Mmysql -u root -p < database/setup.sql



## 🖼️ Project Structure / Projekt Szerkezet
📦 OpenEarthGnomes
├── 📂 database
│   └── setup.sql              # Adatbázis inicializáló szkript
├── 📂 genomes                 # Genomfájlok tárolása
│   ├── Triticum_aestivum.fasta # Búza genoma
│   └── Apis_mellifera.fasta    # Méh genoma
├── 📂 libs                    # Külső könyvtárak
│   └── inih                   # INI fájl parser
├── 📂 src                     # Forráskód
│   ├── DatabaseManager.cpp    # Adatbázis kezelés
│   ├── DatabaseManager.h      
│   ├── GenomeLoader.cpp       # Genom betöltés
│   ├── GenomeLoader.h         
│   └── main.cpp               # Fő program
├── 📜 CMakeLists.txt          # Fordítási konfiguráció
├── 📜 config_sample.ini       # Konfigurációs minta
├── 📜 CONTRIBUTING.md         # Közreműködési útmutató
├── 📜 LICENSE                 # MIT licenc
└── 📜 README.md               # Ez a fájl

## 🚀 Getting Started / Kezdeti lépések
1. **Build the application / Alkalmazás fordítása**  
   Follow the installation steps above / Kövesd a fenti telepítési lépéseket
   
2. **Configure MySQL / MySQL beállítása**  
   Create database with setup.sql / Hozd létre az adatbázist a setup.sql segítségével
   
3. **Run the program / Program futtatása**  
   ```bash
   # Windows
   .\build\Release\GenomeDatabase.exe
   
   # Linux
   ./build/GenomeDatabase
   ```

4. **Upload your first genome / Tölts fel első genomod**  
   ```bash
   GenomeDatabase --upload genomes/Triticum_aestivum.fasta
   ```

**Köszönjük, hogy részese vagy ennek a globális kezdeményezésnek!**  
**Thank you for being part of this global initiative!** 🌍✨
