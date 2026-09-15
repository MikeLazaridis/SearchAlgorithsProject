# AIproject – Register Problem Search Algorithms

Implementation of several search algorithms for solving the **Register Problem**, developed as part of a university assignment for the **2025–2026 academic year**.

## Description

The program receives a starting integer and a target integer and searches for a sequence of predefined operations that transforms the starting value into the target.

Each state of the problem is represented by a node containing:

* The current integer value (`data`)
* The path cost (`g_cost`)
* The heuristic cost (`h_cost`)
* The total estimated cost (`f_cost`)
* The operation (`action`) that produced the node
* A pointer to its parent (`parent`)

Each node can be expanded into up to six children according to the available operations and their corresponding costs.

## Search Algorithms

The project implements four search algorithms:

* **Breadth-First Search (BFS)** – explores the search space level by level using a queue.
* **Depth-First Search (DFS)** – explores the search space depth-first using a stack and stops as soon as a solution is found.
* **Best-First Search** – uses a heuristic function to prioritize the node estimated to be closest to the target.
* **A*** – combines the path cost `g(n)` with the heuristic `h(n)` using:

```text
f(n) = g(n) + h(n)
```

The heuristic used is based on the absolute difference between the current value and the target:

```text
h(n) = |current - target|
```

## Project Structure

```text
AIproject/
│
├── main.c
├── node.c
├── node.h
├── bfs.c
├── bfs.h
├── dfs.c
├── dfs.h
├── best_first.c
├── best_first.h
├── a_star.c
├── a_star.h
├── solutions.txt
├── AIproject.pdf
└── CMakeLists.txt
```

## Compilation

The project uses **CMake** and can be built using CLion or directly with CMake.

The resulting executable is:

```text
AIproject.exe
```

## Usage

The program expects four command-line arguments:

```text
AIproject.exe <method> <start> <end> <output_file>
```

Available methods:

```text
breadth
depth
best_first
a_star
```

### Example

```powershell
.\AIproject.exe best_first 8 25 solutions.txt
```

For A*:

```powershell
.\AIproject.exe a_star 8 25 solutions.txt
```

For BFS:

```powershell
.\AIproject.exe breadth 8 25 solutions.txt
```

For DFS:

```powershell
.\AIproject.exe depth 8 25 solutions.txt
```

## Output

When a solution is found, the program exports the solution to the specified `.txt` file.

The output contains:

1. The number of steps in the solution
2. The total path cost
3. The sequence of operations and resulting states
4. The execution time

Example format:

```text
5 12
start 8 0
operation 10 2
operation 15 3
operation 20 4
operation 25 3
### Execution time: 0.012 seconds.
```

## Execution Timeout

All search algorithms use a predefined execution timeout to prevent the program from running indefinitely on particularly large search spaces.

## Report

The accompanying report describes:

* The Register Problem
* The node and children data structures
* The implementation of the search algorithms
* The heuristic function
* The solution path reconstruction
* Execution-time measurement
* Experimental observations

The report is available in:

```text
AIproject.pdf
```

## Technologies

* **C**
* **CMake**
* **CLion**
* Standard C libraries (`stdio`, `stdlib`, `string`, `time`, `stdbool`)

## Author

**Μιχαήλ Λαζαρίδης**

University assignment – 2025–2026
