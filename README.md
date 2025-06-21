# OpenEarthGnomes
Free data Flora Fauna Gnomes  c++
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
