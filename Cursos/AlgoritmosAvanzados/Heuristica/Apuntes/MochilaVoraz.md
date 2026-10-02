# Greedy Algorithm: Knapsack Package Loading (C++)

## Core Summary

The provided C++ code implements a **greedy algorithm** (algoritmo voraz) to solve a simplified variation of the 0/1 Knapsack Problem. The objective of this specific script is to pack as many heavy packages as possible into a knapsack (mochila) with a fixed weight capacity. It achieves this by sorting the available packages in descending order of weight and iteratively adding them to the knapsack if they fit within the remaining capacity (residuo).

## Key Concepts & Definitions

* **Greedy Algorithm**: An algorithmic paradigm that builds up a solution piece by piece, always choosing the next piece that offers the most immediate and obvious benefit. In this code, the "local optimum" choice is to take the heaviest available package that still fits.
* **0/1 Knapsack Problem (Simplified)**: A combinatorial optimization problem. The "0/1" designation means an item is either completely included (1) or excluded (0); it cannot be fragmented. This code simplifies the classic problem by assuming the value of an item is strictly equivalent to its weight.
* **C++ `std::sort` with Custom Comparator**: The standard library sorting function is used with a custom boolean function (`gt`) to enforce descending order, overriding the default ascending behavior.

## Detailed Breakdown of the Code

### 1. Comparators (`gt` and `lt`)

```cpp
bool gt(int a, int b) { return a > b; }
bool lt(int a, int b) { return a < b; }

```

These functions define the sorting criteria.

* `gt` (greater than) is used to sort the vector in **descending** order.
* `lt` (less than) is provided for **ascending** order, though it remains unused in the current execution.

### 2. Helper Function (`mostrarMochila`)

This function iterates through the `vector<int> paquetes` and prints its contents. It is used to verify the state of the items after sorting.

### 3. Core Logic (`cargarMochila`)

This function dictates the greedy selection process.

1. **Sorting**: `sort(paquetes.begin(), paquetes.end(), gt);` orders the packages from heaviest to lightest.
2. **Iterative Selection**: It loops through the sorted vector. For each package `paquetes[i]`:
* It checks the feasibility condition: `if (residuo - paquetes[i] >= 0)`.
* If true, the package is "inserted": the remaining capacity (`residuo`) is reduced by the package's weight, and the item counter (`numPaquetesIngresados`) increments.
* If false, the package is skipped, and the loop moves to the next lighter package.



### 4. Execution Trace (Based on `main`)

* **Initial Capacity (`peso`)**: 19
* **Initial Packages**: `{2, 1, 2, 4, 12}`
* **Sorted Packages**: `{12, 4, 2, 2, 1}`
* **Iteration Steps**:
1. Check 12: `19 - 12 = 7 >= 0`. (Insert 12). Remaining: 7.
2. Check 4: `7 - 4 = 3 >= 0`. (Insert 4). Remaining: 3.
3. Check 2: `3 - 2 = 1 >= 0`. (Insert 2). Remaining: 1.
4. Check 2: `1 - 2 = -1 < 0`. (Skip). Remaining: 1.
5. Check 1: `1 - 1 = 0 >= 0`. (Insert 1). Remaining: 0.


* **Final Output**:
* Packages inserted: 12, 4, 2, 1.
* Total packages: 4.
* Final residue: 0.



## Critical Analysis & Practical Implications

### Limitations of the Greedy Approach

While the greedy algorithm yields an optimal sequence for the specific inputs provided in `main` (resulting in a residue of 0), **this approach does not guarantee an optimal solution for all 0/1 Knapsack instances**.

**Counter-example:**

* Capacity: 10
* Packages: `{6, 5, 5}`
* **Greedy output (descending)**: Sorts to `{6, 5, 5}`. Takes `6`. Remaining capacity is 4. Cannot take `5` or `5`. Total weight packed = 6. Residue = 4.
* **Optimal output**: Take `{5, 5}`. Total weight packed = 10. Residue = 0.

### Key Takeaways for Application

* **Use Case**: This specific algorithm is highly efficient ($O(N \log N)$ due to sorting) and is appropriate for applications where a "good enough" heuristic approximation is acceptable, or when exact optimality is not strictly required.
* **Optimal Alternative**: If the absolute optimal solution (minimizing residue/maximizing packed weight) is required for any arbitrary set of weights, a **Dynamic Programming** approach (which operates in pseudo-polynomial time, $O(nW)$) must be used instead of this greedy heuristic.