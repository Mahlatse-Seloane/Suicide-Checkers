## **Suicide Checkers (Losing Draughts) ♟️**

This project is a **C++ console-based implementation of Suicide Checkers (also known as Losing Draughts)**, a variant of checkers in which the goal is to lose all pieces or reach a position where no legal moves remain.

The project was originally created during my time at university and is now being revisited as part of an effort to strengthen my software development fundamentals, particularly around program structure, state management, and rule-driven logic. Rather than focusing on adding new features, the emphasis is on improving structure, clarity, and correctness while working within an existing codebase.

---

## **Project overview**

The game models a standard checkers board, pieces, and turn-based gameplay while enforcing the specific rules of Suicide Checkers. The core challenge of the project lies in correctly handling legal moves, forced captures, promotions, and win conditions, all while keeping the code readable and maintainable.

The project is intentionally console-based to keep the focus on **logic, state management, and rule enforcement**, rather than user interface concerns.

---

## Context

### 📘 About Suicide Checkers

Suicide Checkers (also known as **Anti-Checkers**, **Giveaway Checkers**, or **Losing Draughts**) is a variant of checkers where the win condition is 
reversed:

* If you have **no pieces left** or **cannot move anymore**, you **win**.
* Players alternate turns, following standard checkers movement rules.
* The goal is to eliminate your own pieces.

### **Original Project Requirements**

Using the Code::Blocks IDE, we were required to:

1. Develop a program that simulates a game of suicide checkers for different board sizes.
2. Implement two different algorithms that will play suicide checkers against each other.
3. Read in the list of board sizes (n × n where 6 ≤ n ≤ 12 and even) from a file named `input.txt`.
4. Record all moves made by each algorithm and final results in an output file `results.txt`.
5. Bonus: Implement the play of a king piece.
6. Code requirements:
   * No console **input** or **output** allowed.
   * No **global variables** may be used. This will **result in failing** the project.
   * Use at least **one Class**.
   * Use of **Functions**.

### ♟ Board Format

To record moves meaningfully, a standard **labelling system**, shown below, was to be used:

![Board Format](https://imgur.com/aI8JjwZ.png)

* **Player 1** starts on the side beginning with `1`.
* **Player 2** starts on the side with the highest number.

### 📥 Input Format

The input file contained a list of board sizes in the format shown below:

![Input Example](https://imgur.com/rKtzLJs.png)

### 📤 Output Format

The program was to produce an output file named `results.txt`.
This file had to contain:

* The **board size** for the current game.
* Every move made by each player.
* The **final result**:
  * Remaining pieces for each player (`tp1` / `tp2`).
  * Winner (`wp1` or `wp2`) or draw (`d`).

Move Notation:

* **Simple move**: `p1 4-7`
* **Capture move**: `p2 12x5(8)`
* **Multiple captures**: `p2 17x12(14)12x5(8)`

### Example Output

![Output Example](https://imgur.com/JaRF5cw.png)

> Note: Coordinates on the board use row (r) and column (c), with top-left = `r0c0` and bottom-right = `r(n-1)c(n-1)`.

---

## **🧩What this project explores**

This project is being used to practice and reinforce:

* Representing game state (board, pieces, current player) in C++
* Implementing and validating complex rule sets
* Handling edge cases such as forced captures and no-move conditions
* Applying object-oriented concepts such as encapsulation and clear responsibility boundaries
* Gradually refactoring earlier code to reduce duplication and improve readability
* Debugging and reasoning about behaviour in a non-trivial codebase
* Understanding how small design decisions compound as a codebase grows

The goal is not to produce a perfect solution, but to **develop a clearer and more disciplined approach** to building and improving software.

---

## **🥅Why revisit this project**

Reworking this project provides an opportunity to reflect on earlier design decisions and to improve them with a stronger understanding of programming fundamentals. It also encourages working incrementally — making small, testable changes and verifying behaviour as the code evolves.

This mirrors how real-world codebases are often improved: not through rewrites, but through **careful iteration and refinement**.

---

## **Current state and direction**

* Fully playable console-based implementation
* Implements standard Suicide Checkers rules
* Ongoing refactoring focused on correctness, clarity, and simplicity
* Future work will continue to prioritise learning and code quality over feature expansion

---

### 📂 Project Structure

```
SuicideCheckers/
 ├─ 01-include/
 │   ├─ Board.h
 │   ├─ Rules.h
 │   ├─ GameManager.h
 │   .
 │   .
 │   └─ Rules.h
 │  
 ├─ 02-src/
 │   ├─ Board.cpp
 │   ├─ Rules.cpp
 │   ├─ GameManager.cpp
 │   .
 │   .
 │   └─ Rules.cpp
 │   
 ├─ 03-input/
 │   └─ input.txt
 │
 ├─ 04-output/
 │   └─ results.txt
 │
 └─ README.md
```

---

### 🏁 How to Run

```bash
git clone https://github.com/Mahlatse-Seloane/Suicide-Checkers.git
cd SuicideCheckers
g++ -std=c++17 src/*.cpp -o suicide_checkers
./suicide_checkers
```
