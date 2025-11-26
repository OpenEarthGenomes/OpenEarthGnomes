// Így tárolhatod a genomokat:
genomes/
├── Triticum_aestivum.fasta
├── Arabidopsis_thaliana.fasta  
├── Zea_mays.fasta
└── indexes/
    ├── species.index
    ├── taxonomy.index
    └── metadata.json


./GenomeDatabase --init
```

### FASTA fájl betöltése
```bash
./GenomeDatabase --load genomes/Triticum_aestivum.fasta
```

### Könyvtár feldolgozása
```bash
./GenomeDatabase --load-dir ./genomes/
```

### Faj keresése
```bash
./GenomeDatabase --search "Triticum"
```

### Statisztikák
```bash
./GenomeDatabase --stats
```

### Összes faj listázása
```bash
./GenomeDatabase --list
```

---

## 📁 Projekt struktúra

```
OpenEarthGnomes/
├── src/                     # Forráskód
│   ├── main.cpp            # Fő program
│   ├── DatabaseManager.h   # Adatbázis kezelő header
│   ├── DatabaseManager.cpp # Adatbázis kezelő implementáció
│   ├── GenomeLoader.h      # FASTA betöltő header
│   └── GenomeLoader.cpp    # FASTA betöltő implementáció
├── genomes/                # Genomfájlok tárolása
├── libs/                   # Külső könyvtárak
│   └── inih/              # INI fájl parser
├── CMakeLists.txt          # Build konfiguráció
├── config.ini             # Konfigurációs fájl
├── setup.sql              # Adatbázis inicializáló
├── build_windows.bat      # Windows build script
├── build_linux.sh         # Linux build script
└── README.md              # Ez a fájl
```

---

## 🧬 Támogatott formátumok

- **FASTA** (.fasta, .fa, .fas, .fna, .ffn, .faa)
- Automatikus faj név felismerés
- Nagy fájlok támogatása (1GB+ szekvenciák)
- Batch feldolgozás

---

## 🐛 Hibaelhárítás

### Windows problémák

1. **"MySQL könyvtárak nem találhatók"**
   - Ellenőrizd a MySQL Connector/C++ telepítését
   - Állítsd be a `MYSQL_CONNECTOR_ROOT` környezeti változót

2. **"DLL hiányzik"**
   - Másold a `mysqlcppconn8.dll` fájlt az exe mellé
   - Vagy add hozzá a PATH-hoz a MySQL lib könyvtárat

### Linux problémák

1. **"Package not found"**
   ```bash
   sudo apt-get install libmysqlcppconn-dev
   ```

2. **"Connection failed"**
   - Ellenőrizd a MySQL szerver státuszát: `sudo systemctl status mysql`
   - Indítsd el: `sudo systemctl start mysql`

---

## 🤝 Közreműködés

1. Fork-old a repót
2. Hozz létre egy feature branch-et (`git checkout -b feature/AmazingFeature`)
3. Commit-old a változásokat (`git commit -m 'Add some AmazingFeature'`)
4. Push-old a branch-et (`git push origin feature/AmazingFeature`)
5. Nyiss egy Pull Request-et

---

## 📄 Licenc

[MIT License](LICENSE) - Szabadon használható, módosítható, terjeszthető!

---

## 🌟 Jövőbeli tervek

- [ ] Web interfész fejlesztése
- [ ] REST API implementálása
- [ ] Genom összehasonlító eszközök
- [ ] Filogenetikai fa generálás
- [ ] Cloud deployment támogatás
- [ ] Több adatbázis backend (PostgreSQL, SQLite)

---

**Köszönjük, hogy része vagy ennek a globális kezdeményezésnek!** 🌍

*"Egy gen nem csak információ - hanem az élet jövőjének kulcsa."*```

### Statisztikák
```bash
./GenomeDatabase --stats
```

### Összes faj listázása
```bash
./GenomeDatabase --list
```

---

## 📁 Projekt struktúra

```
OpenEarthGnomes/
├── src/                     # Forráskód
│   ├── main.cpp            # Fő program
│   ├── DatabaseManager.h   # Adatbázis kezelő header
│   ├── DatabaseManager.cpp # Adatbázis kezelő implementáció
│   ├── GenomeLoader.h      # FASTA betöltő header
│   └── GenomeLoader.cpp    # FASTA betöltő implementáció
├── genomes/                # Genomfájlok tárolása
├── libs/                   # Külső könyvtárak
│   └── inih/              # INI fájl parser
├── CMakeLists.txt          # Build konfiguráció
├── config.ini             # Konfigurációs fájl
├── setup.sql              # Adatbázis inicializáló
├── build_windows.bat      # Windows build script
├── build_linux.sh         # Linux build script
└── README.md              # Ez a fájl
```

---

## 🧬 Támogatott formátumok

- **FASTA** (.fasta, .fa, .fas, .fna, .ffn, .faa)
- Automatikus faj név felismerés
- Nagy fájlok támogatása (1GB+ szekvenciák)
- Batch feldolgozás

---

## 🐛 Hibaelhárítás

### Windows problémák

1. **"MySQL könyvtárak nem találhatók"**
   - Ellenőrizd a MySQL Connector/C++ telepítését
   - Állítsd be a `MYSQL_CONNECTOR_ROOT` környezeti változót

2. **"DLL hiányzik"**
   - Másold a `mysqlcppconn8.dll` fájlt az exe mellé
   - Vagy add hozzá a PATH-hoz a MySQL lib könyvtárat

### Linux problémák

1. **"Package not found"**
   ```bash
   sudo apt-get install libmysqlcppconn-dev
   ```

2. **"Connection failed"**
   - Ellenőrizd a MySQL szerver státuszát: `sudo systemctl status mysql`
   - Indítsd el: `sudo systemctl start mysql`

---

## 🤝 Közreműködés

1. Fork-old a repót
2. Hozz létre egy feature branch-et (`git checkout -b feature/AmazingFeature`)
3. Commit-old a változásokat (`git commit -m 'Add some AmazingFeature'`)
4. Push-old a branch-et (`git push origin feature/AmazingFeature`)
5. Nyiss egy Pull Request-et

---

## 📄 Licenc

[MIT License](LICENSE) - Szabadon használható, módosítható, terjeszthető!

---

## 🌟 Jövőbeli tervek

- [ ] Web interfész fejlesztése
- [ ] REST API implementálása
- [ ] Genom összehasonlító eszközök
- [ ] Filogenetikai fa generálás
- [ ] Cloud deployment támogatás
- [ ] Több adatbázis backend (PostgreSQL, SQLite)

---

**Köszönjük, hogy része vagy ennek a globális kezdeményezésnek!** 🌍

*"Egy gen nem csak információ - hanem az élet jövőjének kulcsa."*


# GenomeDatabase 🧬

A high-performance database system for storing and managing genome sequences from various species.

## Features

- 🚀 **High Performance** - Optimized for large genome datasets
- 🔍 **Easy Querying** - Simple command-line interface
- 💾 **Multiple Formats** - Support for various FASTA formats
- 🌍 **Global Scale** - Designed for worldwide genomic data

## Quick Start

### Prerequisites

- MySQL Server 8.0+
- CMake 3.15+
- C++17 compatible compiler

### Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/GenomeDatabase.git
cd GenomeDatabase

# Build on Linux
./build_linux.sh

# Build on Windows
build_windows.bat

OpenEarthGnomes/
├── src/ # Source code
│   ├── main.cpp # Main program
│   ├── DatabaseManager.h # Database manager header
│   ├── DatabaseManager.cpp # Database manager implementation
│   ├── GenomeLoader.h # FASTA loader header
│   └── GenomeLoader.cpp # FASTA loader implementation
├── genomes/ # Genome file storage
├── libs/ # External libraries
│   └── inih/ # INI file parser
├── CMakeLists.txt # Build configuration
├── config.ini # Configuration file
├── setup.sql # Database initializer
├── build_windows.bat # Windows build script
├── build_linux.sh # Linux build script
└── README.md # This file

🧬 Supported Formats

· FASTA (.fasta, .fa, .fas, .fna, .ffn, .faa)
· Automatic species name recognition
· Large file support (1GB+ sequences)
· Batch processing

🐛 Troubleshooting

Windows Issues

1. "MySQL libraries not found"
   · Check MySQL Connector/C++ installation
   · Set the MYSQL_CONNECTOR_ROOT environment variable
2. "Missing DLL"
   · Copy the mysqlcppconn8.dll file next to the exe
   · Or add the MySQL lib directory to PATH

Linux Issues

1. "Package not found"
   ```bash
   sudo apt-get install libmysqlcppconn-dev
   ```
2. "Connection failed"
   · Check MySQL server status: sudo systemctl status mysql
   · Start it: sudo systemctl start mysql

🤝 Contributing

1. Fork the repository
2. Create a feature branch (git checkout -b feature/AmazingFeature)
3. Commit your changes (git commit -m 'Add some AmazingFeature')
4. Push the branch (git push origin feature/AmazingFeature)
5. Open a Pull Request

📄 License

MIT License - Free to use, modify, distribute!

🌟 Future Plans

· Web interface development
· REST API implementation
· Genome comparison tools
· Phylogenetic tree generation
· Cloud deployment support
· Multiple database backends (PostgreSQL, SQLite)

---

Thank you for being part of this global initiative! 🌍

"A gene is not just information - it's the key to the future of life."
