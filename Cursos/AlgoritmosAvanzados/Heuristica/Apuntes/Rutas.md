# Greedy Algorithm: Nearest Neighbor Pathfinding (C++)

## Core Summary

The provided C++ code implements a **Nearest Neighbor greedy heuristic** to navigate a directed graph. The algorithm attempts to find a route from a starting node (city 0) to a destination node (city 6) using an adjacency matrix. At each intersection, the algorithm evaluates all immediately available outgoing connections and strictly selects the path with the lowest individual weight (shortest distance), proceeding without backtracking or global cost evaluation.

## Key Concepts & Definitions

* **Adjacency Matrix**: A 2D array representation of a graph. In this code, `mapa[N][N]`, the value at `mapa[i][j]` represents the distance (edge weight) from node `i` to node `j`. A value of `0` indicates no direct connection.
* **Directed Graph**: The connections imply a specific direction. For example, `mapa[0][1]` is 4, but the code does not assume `mapa[1][0]` is also 4.
* **Nearest Neighbor Heuristic**: A greedy strategy that always makes the locally optimal choice at each step (taking the shortest immediate outgoing edge) with the hope of finding a global optimum.

## Detailed Breakdown of the Code

### 1. Graph Representation and Data Structures

```cpp
struct Nodo { int ciudad; int distancia; };
const int N = 8;

```

The `Nodo` struct is used temporarily to pair a target city identifier with the distance to reach it from the current city. `N` defines the static size of the adjacency matrix.

### 2. Neighbor Extraction

```cpp
for (int i = 0; i < N; i++) {
    if (mapa[ciudad][i] > 0) {
        // ... push to vecinos
    }
}

```

At every step of the `while(true)` loop, the algorithm scans the row corresponding to the `ciudad` (current city). Any non-zero value represents a valid outgoing edge, which is appended to the `vecinos` (neighbors) vector.

### 3. The Greedy Choice

```cpp
sort(vecinos.begin(), vecinos.end(), lt);
ciudad = vecinos[0].ciudad;

```

The available neighbors are sorted in ascending order of distance (`lt`). The algorithm unconditionally selects the first element (`vecinos[0]`), adding its distance to `distanciaRecorrida` and updating the current `ciudad`.

### 4. Termination Conditions

The loop terminates under two conditions:

1. **Success**: `ciudad == fin`. The destination is reached.
2. **Failure (Dead End)**: `vecinos.empty()`. The current node has no outgoing edges (all matrix row values are 0), and the algorithm halts completely, printing "No hay solucion."

## Critical Analysis & Practical Implications

### 1. Suboptimality (The Greedy Flaw)

This algorithm **does not guarantee the shortest path**, and the provided `mapa` perfectly demonstrates this failure case.

* **Greedy Execution (Code Output)**: From Node 0, the shortest immediate path is to Node 1 (dist 4). The route taken is `0 -> 1 -> 4 -> 6`. Total distance: **16**.
* **Actual Optimal Path**: If the algorithm took the longer initial step to Node 3 (dist 6), the route would be `0 -> 3 -> 5 -> 6`. Total distance: `6 + 3 + 2` = **11**.
By prioritizing the immediate local minimum, the algorithm is forced into a route with a much higher global cost.

### 2. Fatal Lack of Cycle Detection

The code does not maintain a `visited` list (or boolean array). If the graph contained a cycle (e.g., node 1 connects to node 2, and node 2 connects back to node 1), and those edges were the shortest available, the algorithm would get trapped in an **infinite loop**, alternating between the two nodes forever.

### 3. Inability to Backtrack

Because the algorithm drops all alternative neighbors once a choice is made, it cannot recover from dead ends. If the locally optimal choice leads to a node with no outgoing edges (other than the destination), the program will report "No hay solucion", even if a perfectly valid path existed via a slightly longer initial edge.

### Key Takeaways for Application

* **Do not use this approach for reliable pathfinding or routing.** It is fundamentally broken for general-purpose graph traversal due to the risks of infinite loops and dead-end traps.
* **Optimal Alternatives**:
* To find the guaranteed shortest path in a weighted graph with positive edge weights, you must implement **Dijkstra's Algorithm** or **A* (A-Star)**.
* If you only need to check reachability (whether *any* path exists), use **Breadth-First Search (BFS)** or **Depth-First Search (DFS)**, ensuring you include a `visited` set to prevent infinite loops.