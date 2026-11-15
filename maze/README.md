# Maze Solver — BFS & DFS

A C++ maze solver using **BFS** (Breadth-First Search) and **DFS** (Depth-First Search) matrix traversal.

## Project Structure

| File | Description |
|---|---|
| `MazeSolver.hpp` | Core solver code (class and traversal algorithms) |
| `base.cpp` | Basic empty maze, maze generator and printing |
| `dfs.cpp` | Solves a random maze using **DFS** |
| `bfs.cpp` | Solves a random maze using **BFS** |

## Algorithms

- **DFS** (Depth-First Search): explores one path as far as possible before backtracking. Finds *a* path, not necessarily the shortest.
- **BFS** (Breadth-First Search): explores the maze layer by layer from the start. Guarantees the **shortest path** in an unweighted maze.
