# POO-Tema-2

# **Analiză detaliată a programului Single N-Back**

Acest program implementează jocul **"Single N-Back"**, un exercițiu cognitiv care testează memoria de lucru.

---

## **1. Structura proiectului**
Programul este împărțit în mai multe fișiere:

- **`main.cpp`** – Punctul de intrare în program, gestionează meniul principal.
- **`game.h` / `game.cpp`** – Clasa `SingleNBackGame`, care implementează logica jocului.
- **`stimulus.h` / `stimulus.cpp`** – Clasele pentru stimuli (vizuali, colorați, numerici).
- **`exceptions.h` / `exceptions.cpp`** – Sistemul de excepții.
- **`utils.h` / `utils.cpp`** – Funcții utilitare (afișare grid, clear screen, etc.).

---

## **2. Fluxul programului (ordinea de execuție)**
### **A. Inițializare (`main.cpp`)**
1. **Se afișează meniul principal (`displayMenu()`)**:
   - Utilizatorul alege între:
     - `1` (Joc normal - pătrate negre)
     - `2` (Joc color - emoji)
     - `3` (Joc numeric - cifre)
     - `4` (Ieșire)
2. **Se validează input-ul (`InvalidGameTypeException` dacă e invalid)**.
3. **Se apelează `playGame(int gameType)`**.

### **B. Configurare joc (`utils.cpp` → `playGame()`)**
1. **Se cere nivelul (1-5)**:
   - `N` determină câți pași înapoi trebuie să-și amintească jucătorul.
   - Dacă nivelul e invalid, se aruncă `InvalidLevelException`.
2. **Se cere numărul de runde**.
3. **Se creează un obiect `SingleNBackGame`** cu parametrii:
   - `level` (N)
   - `rounds` (număr de runde)
   - `gameType` (normal/color/number)

### **C. Execuția jocului (`game.cpp` → `SingleNBackGame::play()`)**
1. **Se generează un șir de stimuli (`generateSequence()`)**:
   - Se folosesc clasele derivate din `Stimulus`:
     - `VisualStimulus` (pătrat negru)
     - `ColorStimulus` (🔴, 🟢, 🔵, 🟡)
     - `NumberStimulus` (cifre 0-9)
   - Lungimea secvenței = `rounds + level` (pentru a avea suficiente elemente pentru comparație).
2. **Se afișează gridul 3×3**:
   - La fiecare pas, un stimul este afișat pe poziția aleatoare.
3. **Jucătorul trebuie să răspundă dacă stimulul curent este identic cu cel de acum `N` pași**:
   - `1` = DA, `0` = NU.
   - Se verifică răspunsul în **5 secunde** (altfel, se consideră greșit).
   - Se actualizează scorul (`score++` dacă corect).
4. **La final, se aruncă `GameOverException` cu scorul final**.

### **D. Meniul post-joc (`utils.cpp` → `displayAfterGameMenu()`)**
- **Opțiuni**:
  - `1` = Joacă din nou același mod.
  - `2` = Întoarcere la meniul principal.
- Dacă alegerea e invalidă, se aruncă `InvalidChoiceException`.

---

## **3. Detalii despre clase și moșteniri**
### **🔹 Ierarhia de excepții (`exceptions.h`)**
```cpp
std::exception
└── GameException (abstractă)
    ├── InvalidLevelException
    ├── InvalidInputException
    ├── InvalidGameTypeException
    ├── InvalidChoiceException
    └── GameOverException (cu scor)
```
- **`GameOverException`** este singura care transportă date suplimentare (`score`).

### **🔹 Sistemul de stimuli (`stimulus.h`)**
```cpp
Stimulus (abstract)
├── VisualStimulus (pătrat negru)
├── ColorStimulus (emoji colorat)
└── NumberStimulus (cifră)
```
- Fiecare stimul are:
  - `position` (1-9, poziția pe grid)
  - Metode virtuale:
    - `display()` (afișează pe grid)
    - `matches()` (compară cu alt stimul)
    - `clone()` (pentru copiere)
  - `generateRandom()` (generează stimul aleator)

### **🔹 Clasa principală `SingleNBackGame` (`game.h`)**
- **Atribute**:
  - `level` (N-back)
  - `score`, `rounds`, `currentStreak`, `bestStreak`
  - `gameType` (normal/color/number)
  - `sequence` (vector de stimuli)
  - `gameCount` (static, număr de jocuri create)
- **Metode**:
  - `generateSequence()` – Umple `sequence` cu stimuli aleatorii.
  - `play()` – Rulează jocul pas cu pas.

---

## **4. Librării utilizate**
| Librărie | Rol |
|----------|-----|
| `<iostream>` | I/O (consolă) |
| `<vector>` | Stocare secvențe de stimuli |
| `<memory>` | `shared_ptr` pentru stimuli |
| `<chrono>` | Măsurarea timpului de răspuns |
| `<thread>` | Pauze (`sleep_for`) |
| `<random>` | Generare numere aleatoare |
| `<exception>` | Sistemul de excepții |

---

## **5. Exemplu de rulare**
1. **Pornire**:
   ```
   =================================
          SINGLE N-BACK          
   =================================
   1. Joc normal (patrate negre)
   2. Joc color (emoji colorate)
   3. Joc numeric (cifre)
   4. Iesire
   =================================
   Alege optiunea (1-4): 1
   ```
2. **Configurare**:
   ```
   Introdu nivelul (1-5): 2
   Introdu numarul de runde: 10
   ```
3. **Joc**:
   ```
   Nivel: 2-Back | Scor: 0 | Streak: 0 (Best: 0)

   ⬜ ⬜ ⬜
   ⬜ ⬛ ⬜
   ⬜ ⬜ ⬜

   Introdu raspunsul (1/0): 1
   ```
4. **Final**:
   ```
   Joc terminat! Scor final: 7
   ```

---

## **6.Îndeplinirea cerințelor în codul Single N-Back**

## **1. Funcții virtuale (pure) și polimorfism**
### **Cerințe:**
**Funcții virtuale** (`matches()` și `display()` în `Stimulus`)  
**Apelare prin pointeri la clasa de bază** (`std::shared_ptr<Stimulus>`)  
**Pointerii sunt atribuiti în altă clasă** (`SingleNBackGame` are `std::vector<std::shared_ptr<Stimulus>> sequence`)  

### **Implementare:**
- **Clasa abstractă `Stimulus`**:
  ```cpp
  class Stimulus {
  public:
      virtual ~Stimulus() = default;
      virtual void display(std::vector<std::vector<std::string>>& grid) const = 0;
      virtual bool matches(const std::shared_ptr<Stimulus>& other) const = 0;
      virtual std::shared_ptr<Stimulus> clone() const = 0;
  };
  ```
- **Derivatele (`VisualStimulus`, `ColorStimulus`, `NumberStimulus`)** suprascriu funcțiile:
  ```cpp
  // Exemplu în VisualStimulus
  bool VisualStimulus::matches(const std::shared_ptr<Stimulus>& other) const {
      auto derived = std::dynamic_pointer_cast<VisualStimulus>(other);
      return derived && position == derived->position;
  }
  ```
- **Apelare prin pointer de bază** (în `SingleNBackGame::play()`):
  ```cpp
  sequence[i]->display(grid); // Apel polimorfic
  ```

---

## **2. Constructori virtuali (`clone()`)**
### **Cerințe:**
**Clone este o funcție virtuală care creează o copie**  
**Se folosește în copierea obiectelor (ex: `SingleNBackGame`)**  

### **Implementare:**
- **Metoda `clone()` în fiecare clasă derivată**:
  ```cpp
  std::shared_ptr<Stimulus> VisualStimulus::clone() const {
      return std::make_shared<VisualStimulus>(*this);
  }
  ```
- **Folosit în constructorul de copiere al lui `SingleNBackGame`**:
  ```cpp
  for (const auto& stim : other.sequence) {
      sequence.push_back(stim->clone()); // Copiere polimorfică
  }
  ```

---

## **3. Copy-and-Swap și supraîncărcare `operator=`**
### **Cerințe:**
**Suprascriere `operator=` și constructor de copiere**  
**Folosire `swap` pentru gestionare resurse**  

### **Implementare:**
- **Funcția `swap` pentru fiecare clasă**:
  ```cpp
  void swap(VisualStimulus& a, VisualStimulus& b) noexcept {
      using std::swap;
      swap(a.position, b.position);
  }
  ```
- **`operator=` folosind copy-and-swap**:
  ```cpp
  VisualStimulus& operator=(VisualStimulus other) {
      swap(*this, other);
      return *this;
  }
  ```

---

## **4. `dynamic_cast` și smart pointers**
### **Cerințe:**
**Downcasting cu `std::dynamic_pointer_cast`**  
**Folosire `std::shared_ptr` în loc de pointeri raw**  

### **Implementare:**
- **Verificare tip în `matches()`**:
  ```cpp
  auto derived = std::dynamic_pointer_cast<VisualStimulus>(other);
  if (!derived) return false; // Nu este de același tip
  ```

---

## **5. Ierarhie de excepții**
### **Cerințe:**
**Bază pe `std::exception`**  
**Minim 3 clase de excepții specifice**  
**Folosire în constructori și `main`**  

### **Implementare:**
- **Clasa de bază `GameException`**:
  ```cpp
  class GameException : public std::exception {
  public:
      virtual const char* what() const noexcept override = 0;
  };
  ```
- **Excepții derivate**:
  ```cpp
  class InvalidLevelException : public GameException { /* ... */ };
  class InvalidInputException : public GameException { /* ... */ };
  class GameOverException : public GameException { /* ... */ };
  ```
- **Folosire în cod**:
  ```cpp
  if (level < 1 || level > 5) throw InvalidLevelException();
  ```

---

## **6. Funcții și atribute statice**
### **Cerințe:**
**Atribut static (`gameCount` în `SingleNBackGame`)**  
**Funcție statică (`getGameCount()`)**  

### **Implementare:**
```cpp
class SingleNBackGame {
    static int gameCount; // Numără instanțele
public:
    static int getGameCount() { return gameCount; }
};
```

---

## **7. STL și `const`**
### **Cerințe:**
**Folosire STL (`std::vector`, `std::shared_ptr`)**  
**Maxim `const` (ex: metode `const`, parametri `const&`)**  

### **Exemple:**
```cpp
void display(const std::vector<std::vector<std::string>>& grid) const;
bool matches(const std::shared_ptr<Stimulus>& other) const;
```

---

## **8. Eliminare getters/setters**
### **Cerințe:**
**Minimizare getters/setters**  
**Folosire metode de nivel înalt**  

### **Exemplu:**
- **`SingleNBackGame` nu are getter pentru `sequence`** (se folosește direct în `play()`).

---
