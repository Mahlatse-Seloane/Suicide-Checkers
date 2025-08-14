Suicide Checkers – Requirements Specification

1. Purpose

The goal of this project is to develop a C++ program that simulates a game of suicide checkers between two distinct algorithms, each competing autonomously. The system must support reading board sizes from an input file, limited to even values of n where 6 ≤ n ≤ 12, and generate an output file that logs each algorithm's moves according to a strict format.

The software will be used for educational purposes, demonstrating software engineering practices, game simulation logic, and adherence to strict input/output specifications.

2. Scope

In Scope:
  * Simulating suicide checkers between two AI algorithms.
  * Supporting board sizes of 6×6, 8×8, 10×10, and 12×12 (even sizes between 6 and 12 inclusive).
  * Reading board sizes from a text file (`input.txt`).
  * Writing results to a text file (`results.txt`) in a strict, case- and spacing-sensitive format.
  * Enforcing all game rules described in the project brief, including compulsory captures.

Out of Scope:
  * Graphical user interface or visual representation of the board.
  * Real-time player input or human vs. computer modes.
  * Multiplayer networking.
  * Performance optimization beyond reasonable execution time.

---

3. Goals

* Develop an autonomous simulation that runs without human intervention.
* Ensure strict compliance with formatting and rule enforcement.
* Deliver a clean, modular C++17 codebase that avoids global variables and follows best practices.

---

4. Stakeholders

* Development Team — implements, tests, and documents the solution.
* Project Manager — oversees progress, quality, and adherence to scope.
* Testers — verify correctness, compliance, and robustness of the implementation.
* Client (Lecturer/University) — defines requirements, provides test data, and evaluates deliverables.

---

5. Functional Requirements

Input Handling:
     1.1 The system must read a list of board sizes from a file named `input.txt`.
     1.2 The system must support even board sizes between 6 and 12 inclusive.

Game Simulation:
   2.1 The system must simulate a complete game of suicide checkers for each valid board size.
   2.2 Two distinct AI algorithms must compete autonomously in each simulation.
   2.3 Compulsory captures must always be enforced.
   2.4 If kings are not implemented, pieces reaching the far end of the board can no longer move.

Output Logging:
   3.1 The system must generate a file named `results.txt`.
   3.2 Each game’s log must start with the board size and record all moves in the exact format specified in the project brief.
   3.3 The log must include remaining pieces per player and the winner/draw result at the end of each game.
   3.4 The game history for each board size must be appended to the output file with one empty line between games.

---

6. Non-Functional Requirements

* The program must produce no console output during execution.
* The code must compile successfully with `g++` version 8.2 or higher using C++17 standards.
* The system should process all games in under 30 seconds on a standard laptop.

---

7. Technical & Submission Constraints

* The system must be implemented in C++.
* No global variables may be used.
* The first line of the main source file must contain a single-line comment with the student number in the format:

   ```cpp
   // <StudentNumber>
   ```
---

8. Assumptions

Input:
  * `input.txt` will be correctly formatted with one board size per line.
  * The file will exist in the same directory as the executable.

Game Logic:
  * Compulsory captures always override normal moves.
  * King logic is optional; if not implemented, pieces at the far edge stop moving.

Output:
  * The `results.txt` file will be overwritten each time the program is run unless otherwise specified.
  * All moves must be logged exactly per the specification.

Testing:
  * The system will be tested using standard inputs provided by the client/university.
  * No external libraries will be used or tested against.

Performance:
  * The system should complete all simulations for a given input file within a reasonable time (e.g., under 30 seconds for 10 games on a standard laptop).

---

9. Success Criteria

* All valid input board sizes produce a complete and correctly formatted game log.
* The system enforces all game rules without exception.
* Output files pass automated validation against the project specification.
* Code follows modular, maintainable design principles and compiles without warnings.

---

10. Glossary

* Suicide Checkers — A variation of checkers where the goal is to lose all pieces or be unable to move.
* Compulsory Capture — A rule requiring a player to take a capture if available.
* King — A promoted piece able to move forward and backward diagonally.
* Stalemate — A draw condition where neither player can make a valid move.

---
