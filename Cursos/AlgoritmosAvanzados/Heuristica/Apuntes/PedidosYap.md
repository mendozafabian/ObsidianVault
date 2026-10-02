# Greedy Algorithm: Nearest Neighbor Pathfinding (Dead End Failure)

## Core Summary

This C++ code implements a **Nearest Neighbor greedy heuristic** for traversing a directed graph, attempting to find a route from a start node (0) to a destination node (7). It operates by evaluating immediately available outgoing edges and strictly selecting the path with the lowest distance weight. This specific execution serves as a practical demonstration of how a greedy algorithm without backtracking can fail to find an existing solution by trapping itself in a dead end.

## Key Concepts & Definitions

* **Local Optimum vs. Global Optimum**: A greedy algorithm makes choices that look best in the immediate moment (the local optimum). In pathfinding, this means taking the shortest available step without considering the overall route. This often prevents the algorithm from finding the best overall solution (the global optimum).
* **Dead End (Sink Node)**: A node in a directed graph that has incoming edges but no outgoing edges. If an algorithm reaches this node and it is not the destination, it is trapped.
* **Backtracking**: An algorithmic technique (absent in this code) where, upon reaching a dead end, the program returns to a previous decision point and tries an alternative path.

## Detailed Breakdown of the Code

### 1. Data Structures

```cpp
#define MAX 8
struct Nodo { int punto; int distancia; };

```

* `MAX` defines the 8x8 dimensions of the adjacency matrix.
* `Nodo` pairs a target city index (`punto`) with the weight of the edge leading to it (`distancia`).

### 2. The Heuristic Loop

```cpp
sort(vecinos.begin(), vecinos.end(), lt);
ciudad = vecinos[0].punto;

```

At every iteration, the algorithm scans the matrix row for the current city, collects all non-zero connections into the `vecinos` vector, sorts them in ascending order (`lt`), and unconditionally moves to the closest neighbor (`vecinos[0]`).

### 3. Execution Trace: The "Dead End" Trap

The code attempts to navigate from `0` to `7`. This execution perfectly exposes the algorithm's inability to backtrack.

* **Step 1 (City 0)**: Neighbors are 1 (dist 4), 2 (dist 5), and 3 (dist 6). The greedy choice is **1**.
* **Step 2 (City 1)**: The only neighbor is **4** (dist 2). The algorithm moves to 4.
* **Step 3 (City 4)**: The only neighbor is **6** (dist 10). The algorithm moves to 6.
* **Step 4 (City 6)**: Node 6 has no outgoing edges (row 6 is all `0`s). `vecinos` is empty.
* **Resolution**: The current city (6) is not the destination (7). Because `vecinos` is empty, the program prints `"No hay solucion."` and halts.

## Critical Analysis & Practical Implications

### 1. Failure to Find Existing Solutions

While the algorithm reported no solution, **a valid and highly efficient path exists**:

* `0 -> 2 -> 7` (Total distance: 5 + 3 = **8**).
The algorithm missed this path entirely because the initial step to node 2 (dist 5) was slightly more expensive than the step to node 1 (dist 4). By strictly following the local minimum, the algorithm doomed itself to a dead end.

### 2. Lack of Memory and Recovery

Because the algorithm clears the `vecinos` vector at the start of every `while` loop iteration, it suffers from total amnesia. It discards the alternative paths it saw at node 0 (nodes 2 and 3). To fix this, the algorithm would require a stack or a recursive structure to remember untried branches (enabling backtracking).

### Key Takeaways for Application

* **Unreliability**: This code proves that a strict greedy approach is entirely unsuitable for reliable pathfinding in graphs with dead ends. It cannot guarantee a shortest path, nor can it even guarantee finding a path if one exists.
* **Correct Algorithmic Solutions**:
* To guarantee the shortest path based on edge weights: Implement **Dijkstra's Algorithm**.
* To guarantee finding a path if one exists (without caring about weight): Implement **Depth-First Search (DFS)** with backtracking, or **Breadth-First Search (BFS)**.