# POO-Tema-2

### **Descrierea Proiectului: Jocul Single n-Back**  

#### **Enunț**  
Single n-Back este un joc de antrenament cognitiv care testează memoria de lucru și abilitățile de concentrare. Jocul prezintă o succesiune de stimuli vizuali (pătrate negre pe o grilă 3x3), iar jucătorul trebuie să determine dacă stimulul curent este identic cu cel de la `n` pași în urmă.  

#### **Cerințe**  
1. **Implementarea Ierarhiei de Excepții**  
   - Clase de excepții pentru: nivel invalid, input invalid și sfârșitul jocului.  
   - Moștenire din `std::exception`.  

2. **Clasa `Stimulus` și Derivata `VisualStimulus`**  
   - `Stimulus`: clasă abstractă cu metode virtuale pure (`display`, `matches`, `clone`).  
   - `VisualStimulus`: implementează un stimul vizual (poziție pe grilă).  

3. **Clasa `SingleNBackGame`**  
   - Gestionează logica jocului:  
     - Generare secvență aleatoare de stimuli.  
     - Afișare pe grid 3x3.  
     - Validare răspunsuri (1 = match, 0 = nu match).  
     - Calcul scor și streak-uri.  

4. **Interfață Utilizator Simplă**  
   - Afișare grid cu pătrate (⬛ = stimul curent, ⬜ = gol).  
   - Timp limitat de răspuns (5 secunde).  
   - Feedback imediat (corect/gresit + scor).  

5. **Funcționalități Adiționale**  
   - Clear screen între runde.  
   - Sistem de dificultate (nivel `n` între 1-5).  
   - Best streak și scor final.  

---

### **Bibliografie / Surse de Inspirație**  
1. **n-Back Task**  
   - Jaeggi, S. M., et al. (2008). *"Improving fluid intelligence with training on working memory."* PNAS.  
   - [https://en.wikipedia.org/wiki/N-back](https://en.wikipedia.org/wiki/N-back)  

2. **Implementări Existente**  
   - Dual N-Back (joc open-source): [https://github.com/petrkle/dual-n-back](https://github.com/petrkle/dual-n-back)  
   - Brain Workshop (Python): [http://brainworkshop.sourceforge.net/](http://brainworkshop.sourceforge.net/)  

3. **C++ Resources**  
   - Random Number Generation: [https://en.cppreference.com/w/cpp/numeric/random](https://en.cppreference.com/w/cpp/numeric/random)  
   - Smart Pointers: [https://en.cppreference.com/w/cpp/memory/shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)  

---

### **Exemplu de Interacțiune**  
```
Bine ai venit la Single n-Back!  
Introdu nivelul (1-5): 2  
Introdu numarul de runde: 10  

Pregatire...  
⬜⬜⬜  
⬜⬜⬜  
⬜⬜⬜  

Tasteaza 1 daca patratul negru este in aceeasi pozitie ca acum 2 pasi, altfel 0.  

[Nivel: 2-Back | Scor: 0 | Streak: 0]  
⬜⬛⬜  
⬜⬜⬜  
⬜⬜⬜  
Introdu raspunsul (1/0): 1  
CORECT! (+1 punct) Scor: 1 | Streak: 1  
```  
