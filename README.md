# ΕΠΕΞΗΓΗΣΗ ΚΩΔΙΚΑ ΓΙΑ ΠΑΡΟΥΣΙΑΣΗ

## 1. ΔΟΜΗ ΤΟΥ PROJECT (ΠΟΥ ΒΡΙΣΚΕΤΑΙ ΤΙ)
* **GlobalState.h / .cpp**: Ο "εγκέφαλος" του παιχνιδιού. Περιέχει τον Γράφο, τη λίστα των αντικειμένων και το game loop.
* **GameObject.h**: Η βασική κλάση (γονέας) και η δομή του Κόμβου (Node).
* **Snake.h / .cpp**: Η λογική του παίκτη (κίνηση στο γράφο, ουρά).
* **Food.h / .cpp**: Το φαγητό που εμφανίζεται σε τυχαίους κόμβους.
* **main.cpp**: Η είσοδος του προγράμματος, ρυθμίζει τα callbacks της SGG.

---

## 2. ΥΛΟΠΟΙΗΣΗ ΜΕ ΓΡΑΦΟ (GRAPH IMPLEMENTATION)
**Ερώτηση:** Πώς υλοποίησες την πίστα/πλέγμα; Είναι πίνακας;
**Απάντηση:** Όχι, είναι Γράφος (Grid Graph).

### Α. Η ΔΟΜΗ ΤΟΥ ΚΟΜΒΟΥ (NODE)
* **Αρχείο:** `GameObject.h` (γραμμές 11-20).
* Έχω φτιάξει ένα `struct Node`.
* Κάθε κόμβος περιέχει συντεταγμένες (x, y) για τη ζωγραφική.
* **ΤΟ ΣΗΜΑΝΤΙΚΟΤΕΡΟ:** Κάθε κόμβος έχει 4 δείκτες (pointers) προς τους γείτονές του: `Node* up, *down, *left, *right`.
* Έτσι επιτυγχάνεται η συνδεσιμότητα.

### Β. ΤΟ ΧΤΙΣΙΜΟ ΤΟΥ ΓΡΑΦΟΥ
* **Αρχείο:** `GlobalState.cpp` -> συνάρτηση `buildGraph()`.
* Δημιουργώ δυναμικά τους κόμβους.
* Συνδέω τους δείκτες κάθε κόμβου με τους γειτονικούς του (π.χ. `curr->right = grid[i+1][j]`).

### Γ. Η ΚΙΝΗΣΗ ΤΟΥ ΦΙΔΙΟΥ ΣΤΟΝ ΓΡΑΦΟ
* **Αρχείο:** `Snake.cpp` -> συνάρτηση `update()`.
* Δεν μεταβάλλω τα x, y pixels για να κουνηθώ.
* Αλλάζω τον δείκτη `m_head_node` ώστε να δείχνει στον επόμενο γείτονα.
* Παράδειγμα: `nextNode = m_head_node->right` (αν πηγαίνω δεξιά).

---

## 3. ΑΝΤΙΚΕΙΜΕΝΟΣΤΡΕΦΗΣ ΠΡΟΓΡΑΜΜΑΤΙΣΜΟΣ (OOP)

### Α. ΚΛΗΡΟΝΟΜΙΚΟΤΗΤΑ (INHERITANCE)
* **Αρχείο:** `GameObject.h` (γραμμή 24).
* Έχω την κλάση `GameObject` ως Abstract Base Class (Αφηρημένη Βασική Κλάση).
* Περιέχει pure virtual συναρτήσεις: `virtual void update() = 0;`.
* **Αρχεία:** `Snake.h` και `Food.h`.
* Οι κλάσεις `Snake` και `Food` κληρονομούν από την `GameObject` (`public GameObject`).
* Υλοποιούν υποχρεωτικά τις `update()` και `draw()`.

### Β. ΠΟΛΥΜΟΡΦΙΣΜΟΣ (POLYMORPHISM)
* **Αρχείο:** `GlobalState.h` (γραμμή 18).
* Χρησιμοποιώ ένα vector με δείκτες στον γονέα: `std::vector<GameObject*> m_objects`.
* Μέσα σε αυτό το vector αποθηκεύω παιδιά (`new Snake()`, `new Food()`).
* **Αρχείο:** `GlobalState.cpp` -> συνάρτηση `update(float ms)`.
* Ο πολυμορφισμός συμβαίνει στη γραμμή: `for (auto* obj : m_objects) obj->update();`.
* Εδώ, το πρόγραμμα αποφασίζει δυναμικά (κατά την εκτέλεση) ποια `update` θα καλέσει (του φιδιού ή του φαγητού), ανάλογα με το τι είναι το αντικείμενο.

---

## 4. ΣΥΓΚΡΟΥΣΕΙΣ (COLLISIONS)
**Ερώτηση:** Πώς ελέγχεις αν το φίδι έφαγε το φαγητό ή χτύπησε τοίχο;

### Α. SNAKE VS FOOD (Σύγκριση Δεικτών)
* **Αρχείο:** `GlobalState.cpp` -> συνάρτηση `update()` (γραμμή 128).
* Δεν μετράω αποστάσεις με pixels.
* Συγκρίνω αν οι δείκτες είναι ίδιοι: `if (snake->getHeadNode() == food->getNode())`.
* Αν δείχνουν στον ίδιο κόμβο μνήμης, τότε υπάρχει σύγκρουση.

### Β. SNAKE VS WALL (Τοίχος)
* **Αρχείο:** `Snake.cpp` -> συνάρτηση `update()`.
* Αν προσπαθήσω να πάω σε κόμβο που δεν υπάρχει (π.χ. `m_head_node->right == nullptr`), σημαίνει ότι βγήκε από τον γράφο.
* Άρα έχουμε Game Over.

### Γ. SNAKE VS SELF (Ουρά)
* **Αρχείο:** `Snake.cpp` -> συνάρτηση `update()`.
* Η ουρά είναι ένα `vector<Node*>`.
* Ελέγχω αν ο `nextNode` υπάρχει μέσα στη λίστα της ουράς.

---

## 5. DESIGN PATTERNS

### SINGLETON PATTERN
* **Αρχείο:** `GlobalState.h`.
* Η κλάση `GlobalState` είναι Singleton.
* Έχει έναν static δείκτη `m_instance`.
* Ο κατασκευαστής είναι `private`, ώστε να μην μπορεί κανείς να φτιάξει 2ο GlobalState.
* Η πρόσβαση γίνεται παντού μέσω της `GlobalState::getInstance()`.

---

## 6. ΒΙΒΛΙΟΘΗΚΗ SGG (Simple Game Graphics)
* **Input:** Χρησιμοποιώ την `graphics::getKeyState` (π.χ. στο Snake.cpp για τα βελάκια).
* **Rendering:**
    * `graphics::drawRect`: Για τους κόμβους και το σώμα του φιδιού.
    * `graphics::drawDisk`: Για το φαγητό και τα μάτια του φιδιού.
    * `graphics::drawText`: Για το σκορ και τα μηνύματα.
    * `graphics::setOrientation`: Στο Snake.cpp, για να περιστρέφω το κεφάλι ανάλογα με την κατεύθυνση.
* **Audio:** `graphics::playSound` (για εφέ) και `playMusic` (για background).
* **Callbacks:** Στο `main.cpp` ορίζω τις `setDrawFunction` και `setUpdateFunction`.



# CODE EXPLANATION FOR PRESENTATION

## 1. PROJECT STRUCTURE (WHERE EVERYTHING IS)
* [cite_start]**GlobalState.h / .cpp**: The "brain" of the game. [cite: 1] [cite_start]It contains the Graph, the list of objects, and the game loop. [cite: 2]
* [cite_start]**GameObject.h**: The base class (parent) and the Node structure. [cite: 3]
* [cite_start]**Snake.h / .cpp**: The player logic (movement on the graph, tail). [cite: 4]
* [cite_start]**Food.h / .cpp**: The food that appears on random nodes. [cite: 5]
* [cite_start]**main.cpp**: The program entry point; it configures the SGG callbacks. [cite: 6]

---

## 2. GRAPH IMPLEMENTATION
**Question:** How did you implement the level/grid? Is it an array?
[cite_start]**Answer:** No, it is a **Grid Graph**. [cite: 7]

### A. THE NODE STRUCTURE
* **File:** `GameObject.h` (lines 11-20)
* [cite_start]I have created a `struct Node`. [cite: 8]
* [cite_start]Each node contains coordinates (x, y) for drawing. [cite: 9]
* [cite_start]**MOST IMPORTANT:** Each node has 4 pointers to its neighbors: `Node* up, *down, *left, *right`. [cite: 10]
* [cite_start]This achieves connectivity. [cite: 11]

### B. BUILDING THE GRAPH
* **File:** `GlobalState.cpp` -> function `buildGraph()`
* I dynamically create the nodes.
* [cite_start]I connect the pointers of each node to its neighbors (e.g., `curr->right = grid[i+1][j]`). [cite: 12]

### C. SNAKE MOVEMENT ON THE GRAPH
* [cite_start]**File:** `Snake.cpp` -> function `update()` [cite: 13]
* I do not modify x, y pixels to move.
* [cite_start]I change the `m_head_node` pointer to point to the next neighbor. [cite: 14]
* [cite_start]Example: `nextNode = m_head_node->right` (if moving right). [cite: 14]

---

## [cite_start]3. OBJECT-ORIENTED PROGRAMMING (OOP) [cite: 15]

### A. INHERITANCE
* **File:** `GameObject.h` (line 24)
* I have the `GameObject` class as an **Abstract Base Class**.
* [cite_start]It contains pure virtual functions: `virtual void update() = 0;`. [cite: 16]
* [cite_start]**Files:** `Snake.h` and `Food.h` [cite: 17]
* [cite_start]The `Snake` and `Food` classes inherit from `GameObject` (`public GameObject`). [cite: 17]
* [cite_start]They mandatorily implement `update()` and `draw()`. [cite: 18]

### B. POLYMORPHISM
* **File:** `GlobalState.h` (line 18)
* [cite_start]I use a vector with pointers to the parent: `std::vector<GameObject*> m_objects`. [cite: 18]
* [cite_start]Inside this vector, I store children (`new Snake()`, `new Food()`). [cite: 19]
* [cite_start]**File:** `GlobalState.cpp` -> function `update(float ms)` [cite: 20]
* [cite_start]Polymorphism happens at the line: `for (auto* obj : m_objects) obj->update();` [cite: 20]
* [cite_start]Here, the program decides dynamically (at runtime) which `update` to call (the snake's or the food's), depending on what the object is. [cite: 20]

---

## [cite_start]4. COLLISIONS [cite: 21]
**Question:** How do you check if the snake ate the food or hit a wall?

### [cite_start]A. SNAKE VS FOOD (Pointer Comparison) [cite: 22]
* **File:** `GlobalState.cpp` -> function `update()` (line 128)
* [cite_start]I do not measure distances with pixels. [cite: 22]
* [cite_start]I compare if the pointers are identical: `if (snake->getHeadNode() == food->getNode())`. [cite: 23]
* [cite_start]If they point to the same memory node, then there is a collision. [cite: 24]

### [cite_start]B. SNAKE VS WALL (Wall) [cite: 25]
* **File:** `Snake.cpp` -> function `update()`
* [cite_start]If I try to go to a node that does not exist (e.g., `m_head_node->right == nullptr`), it means I went out of the graph. [cite: 25]
* [cite_start]Therefore, it is Game Over. [cite: 26]

### C. SNAKE VS SELF (Tail)
* **File:** `Snake.cpp` -> function `update()`
* [cite_start]The tail is a `vector<Node*>`. [cite: 26]
* [cite_start]I check if the `nextNode` exists inside the tail list. [cite: 27]

---

## [cite_start]5. DESIGN PATTERNS [cite: 28]

### SINGLETON PATTERN
* **File:** `GlobalState.h`
* The `GlobalState` class is a Singleton.
* [cite_start]It has a static pointer `m_instance`. [cite: 29]
* [cite_start]The constructor is `private`, so no one can create a 2nd GlobalState. [cite: 29]
* [cite_start]Access is done everywhere via `GlobalState::getInstance()`. [cite: 30]

---

## 6. SGG LIBRARY (Simple Game Graphics)
* [cite_start]**Input:** I use `graphics::getKeyState` (e.g., in Snake.cpp for arrow keys). [cite: 30]
* [cite_start]**Rendering:** [cite: 31]
    * [cite_start]`graphics::drawRect`: For the nodes and the snake's body. [cite: 31]
    * [cite_start]`graphics::drawDisk`: For the food and the snake's eyes. [cite: 32]
    * [cite_start]`graphics::drawText`: For the score and messages. [cite: 32]
    * [cite_start]`graphics::setOrientation`: In Snake.cpp, to rotate the head according to the direction. [cite: 33]
* [cite_start]**Audio:** `graphics::playSound` (for effects) and `playMusic` (for background). [cite: 34]
* [cite_start]**Callbacks:** In `main.cpp`, I define `setDrawFunction` and `setUpdateFunction`. [cite: 34]
