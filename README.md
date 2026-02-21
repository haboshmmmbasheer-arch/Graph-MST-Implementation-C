# Minimum Spanning Tree (MST) in C — Prim & Kruskal

This project builds a weighted undirected graph of cities and computes the **Minimum Spanning Tree (MST)** using:
- **Prim’s Algorithm** (with a Min-Heap priority queue)
- **Kruskal’s Algorithm** (with a Min-Heap + cycle check)

The program also measures execution time for each algorithm using `clock()`.

## Implemented Data Structures
- **Graph (Adjacency List)**: an array of linked lists (`Graph->Array[i].head`)
- **Min-Heap (Priority Queue)**: stores edges as `(src, dest, distance)`
- **Visited Arrays**:
  - For Prim: to track visited cities
  - For Kruskal: DFS-based connectivity check to avoid cycles

## Input File (cities.txt)
The program reads edges from a file named `cities.txt` with the format:

`CityA#CityB#Distance`

Example:
Ramallah#Nablus#50
Nablus#Jenin#30

## Program Menu
1. Load cities (build graph from file)
2. Apply Prim’s Algorithm (start from a chosen city)
3. Apply Kruskal’s Algorithm
4. Compare both algorithms (prints execution time)
5. Exit

## Output
- Prints MST edges like:
  - `From CityA To CityB : X Km`
- Prints total MST cost:
  - `Total cost = ...`
- Prints execution time:
  - `prims took ... sec to execute`
  - `Kruskal took ... sec to execute`

## How to Compile & Run
Compile:
```bash
gcc main.c -o mst

./mst
