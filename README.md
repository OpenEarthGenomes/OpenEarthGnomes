# 🌱 OpenEarthGenomes Project  
**A Föld élőlényeinek genomtára – az élet újjáépítéséhez atomkatasztrófa után**  

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

1. Telepítsd a **Visual Studio 2022**-t (Community verzió ingyenes)
2. A telepítőben jelöld be:
   - `Desktop development with C++`
   - `C++ CMake tools for Windows`
3. Töltsd le a [MySQL Connector/C++ 8.0.37](https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-8.0.37-winx64.zip) fájlt
4. Csomagold ki pl.: `C:\mysql-connector`
5. Indítsd el a Visual Studio-t és válaszd "Open a local folder"
6. Tallózd ki a projekt mappáját
7. Kattints a "Build" menüre → "Build All"
