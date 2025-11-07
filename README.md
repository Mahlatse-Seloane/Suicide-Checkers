# Suicide Checkers ♟️

*A C++17 console simulation of the suicide variant of checkers where losing is winning, between two different AI.*

The program:

* Reads a list of board sizes (`n × n` where 6 ≤ n ≤ 12) from a file named `input.txt`.
* Simulates games between the two algorithms for each board size.
* Records all moves and final results in an output file `results.txt`.

---

## ️⃣ Project Goals / Motivation

As mentioned in the main page, many of the projects here were originally completed during my time at university and I am now revisiting them with a more 
professional mindset.

Suicide Checkers is one of those projects I chose to revisit. The project was meant to expose us to many key aspects of engineering and software 
development. In revisiting these projects, my aim is not just to write functional code, but to also explore professional software engineering practices.

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

## Requirements Extraction

This section formalizes the problem definition from the original brief into structured functional and non-functional requirements.
Functional requirements describe what the system must do, while non-functional requirements capture how well it should perform.
Extracting them clearly establishes traceability from the problem statement to the implementation.

### Functional Requirements

* Read board sizes from `input.txt`.
* Validate sizes (even number, 6–12).
* Simulate a full Suicide Checkers game per size.
* Two autonomous AIs must compete.
* Compulsory captures must be enforced.
* Log all moves and results to `results.txt`.

### Non-Functional Requirements

* No console I/O.
* No global variables.
* Must compile under `-std=c++17`.
* Should complete all runs in <30 seconds.

---

## Implementation

### Approach

The implementation focused on modularity, reusability, and clarity rather than quick fixes. Each module handles a single concern, and communication 
between them happens through well-defined interfaces.

Key design aims:

* Clearly defined responsibilities per class.
* Consistent and reproducible file-based I/O.
* Expandable AI framework for multiple strategies and difficulty levels.
* Avoiding global state.
* Clean separation between *game engine*, *rules*, and *AI*.

---

## 🧩 System Overview

This section outlines the major subsystems and their roles in the simulation. The system was broken down into multiple layers, each abstracting a specific 
responsibility to make the program easier to test, extend, or replace without breaking other parts.

| Layer       | Purpose                                     | Key Classes                           |
| ----------- | ------------------------------------------- | ------------------------------------- |
| Input Layer | Reads and validates board sizes             | `InputHandler`                        |
| Game Engine | Manages board state, moves, and turns       | `GameManager`, `Board`, `Rules`       |
| AI Layer    | Encapsulates decision logic for each player | `PlayerType`, `SuicideAI`, `RandomAI` |
| Evaluation  | Determines when the game ends and who wins  | `ResultEvaluator`                     |
| Logging     | Records all moves and results               | `GameLogger`                          |

---

## 🧱 Architecture Summary

The architecture was designed around **clear responsibility boundaries**. Each module has a narrow, explicit purpose and interacts through minimal shared 
state. This promotes easier debugging and independent evolution of features.

| Module          | Description                                                                                                     |
| --------------- | --------------------------------------------------------------------------------------------------------------- |
| main.cpp        | Entry point, loads input & starts simulations.                                                                  |
| InputHandler    | Parses and filters board sizes from file.                                                                       |
| GameManager     | Controls turn order, move execution, crowning, continuations.                                                   |
| Board           | Stores and updates board state.                                                                                 |
| BoardMapper     | Converts board coordinates ↔ square IDs.                                                                        |
| Rules           | Generates legal moves, enforces mandatory capture.                                                              |
| PlayerType      | Base class for players; defines common interface.                                                               |
| SuicideAI       | Attempts to lose pieces strategically.                                                                          |
| RandomAI        | Selects random valid moves for baseline comparison.                                                             |
| ResultEvaluator | Determines terminal conditions and winner.                                                                      |
| GameLogger      | Writes every move and final results to file.                                                                    |
| Move            | Core struct used to represent a single move (from, to, and captured piece). Shared across AI and rules modules. |
| EndResults      | Defines result data (token counts, winner, and reason) used by `ResultEvaluator` and `GameLogger`.              |


---

## ⚙️ How Modules Interact

The diagram below shows the data and control flow among core components. The arrows represent dependencies and data passing between modules.

```
input.txt
 ↓
InputHandler
 ↓
GameManager → Rules → BoardMapper
 ↓           ↓
Players (AI implementations)
 ↓
ResultEvaluator
 ↓
GameLogger → results.txt
```

---

## ⚙️ Design Principles & Decisions

This project followed several key software design principles to ensure maintainability and extensibility:

* **Pure modularity** - no global variables.
* **Separation of concerns** - each class focuses on a single task.
* **Stateless rule enforcement** - `Rules` and `BoardMapper` are reusable across game types.
* **Board as the source of truth** - ensures consistent, synchronized game state.
* **AI pluggability** - new player strategies can be added without modifying the core engine.
* **File-driven execution** - allows fully automated testing with no console interaction.

---

### 🏁 How to Run

```bash
git clone https://github.com/Mahlatse-Seloane/Suicide-Checkers.git
cd SuicideCheckers
g++ -std=c++17 src/*.cpp -o suicide_checkers
./suicide_checkers
```

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

### Key Design Decisions

This section highlights specific technical and architectural choices made during development. Each decision was guided by the goal of producing 
maintainable, modular, and testable software, not just functional output. These design decisions were important because they helped structure the project 
in a way that clearly separates responsibilities, makes debugging simpler, and supports future extensions such as new AI types or rule variants.

* Mandatory capture logic implemented inside `Rules` for engine clarity.
  → Keeps `GameManager` focused on flow control rather than game logic details.

* Board stored as characters for lightweight representation.
  → Simplifies debugging and output logging, while keeping the format compatible with text-based files.

* `SuicideAI` favors self-sacrificing or exposure moves.
  → Provides behavior aligned with the core objective of Suicide Checkers, distinguishing it from standard play.

* Random AI provides baseline unpredictability for comparison.
  → Offers a benchmark against which more advanced AI strategies can be tested and improved.

---

## 💡 Reflection

Rebuilding this project helped deepen my understanding of:

* Architectural design
* AI behavior modeling
* State management
* Simulation-driven development
* Applying professional engineering thinking to academic projects

This project marks a shift from “making it work” to **making it maintainable**, balancing clarity, scalability, and correctness.

---

## 🚀 Next Steps

* 🤖 Expand AI intelligence (heuristics, evaluation functions, or search-based strategies).
* 🎮 Runtime mode selection (allow the user to choose between Suicide or Normal Checkers).
* 🧍‍♂️ Add player choice: human vs AI or AI vs AI.
* 👑 Extend and stress-test king logic for advanced rule cases.

---

## Technologies Used

| Language | Tools             |
| -------- | ----------------- |
| C++17    | g++, Code::Blocks |

---

## 👤 Author

**Mahlatse Seloane**
BEngSc (Digital Arts) - Wits University
Game Developer / Software Developer

> A university project revisited with a professional engineering mindset.

---

## 🪪 License

MIT - free for learning & research use.

---
