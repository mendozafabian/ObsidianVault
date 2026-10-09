# Greedy Algorithm: 0/1 Knapsack via Value-to-Weight Ratio (C++)

## Core Summary

This C++ script implements a **greedy heuristic** to solve the **0/1 Knapsack Problem** (referred to here as loading a container). The algorithm aims to maximize the total profit (`ganancia`) without exceeding the container's weight capacity (`peso`). It does this by calculating the **value-to-weight ratio** of each package, sorting them in descending order of "efficiency," and iteratively packing the most efficient items that fit into the remaining space.

## Key Concepts & Definitions

* **0/1 Knapsack Problem**: A classic combinatorial optimization problem. You have a set of items, each with a weight and a value. You must determine the collection of items to include in a collection so that the total weight is less than or equal to a given limit and the total value is as large as possible. "0/1" means items cannot be fractioned; they are either entirely included or entirely excluded.
* **Value-to-Weight Ratio (Densidad de Valor)**: The mathematical core of this heuristic. By dividing profit by weight (`ganancia / peso`), the algorithm determines how much profit is generated *per unit of weight*.
* **Type Casting in C++ Division**: In C++, dividing an `int` by an `int` results in integer division (truncating decimals). The code uses `(double)` casting to ensure floating-point division, which is critical for accurate ratio comparison.

## Detailed Breakdown of the Code

### 1. Data Structure and Heuristic Comparators

```cpp
struct Paquete { int ganancia; int peso; };

bool gt(Paquete a, Paquete b) {
    return (double)a.ganancia / a.peso > (double)b.ganancia / b.peso;
}

```

The `gt` comparator enforces a strict descending order based on efficiency.

* *Note on robustness*: If `peso` were `0`, this would cause a divide-by-zero error. In knapsack contexts, weight is assumed to be strictly positive, but in production code, this edge case should be handled.

### 2. Core Greedy Logic

```cpp
sort(paquetes.begin(), paquetes.end(), gt);
// ...
if (residuo - paquetes[i].peso >= 0) {
    residuo -= paquetes[i].peso;
    ganancia += paquetes[i].ganancia;
}

```

1. **Sort**: The packages are ordered from highest value-to-weight ratio to lowest.
2. **Iterate and Pack**: The loop checks each item in the sorted list. If the item's weight is less than or equal to the `residuo` (remaining capacity), it is packed. The profit is added, and the capacity is reduced. If it does not fit, it is simply skipped.

### 3. Execution Trace (Based on `main`)

* **Initial Capacity**: 16
* **Packages** (Value, Weight) $\rightarrow$ Ratio:
* A: {10, 2} $\rightarrow$ Ratio: 5.0
* B: {15, 3} $\rightarrow$ Ratio: 5.0
* C: {10, 5} $\rightarrow$ Ratio: 2.0
* D: {24, 12} $\rightarrow$ Ratio: 2.0
* E: {8, 2} $\rightarrow$ Ratio: 4.0


* **Sorted Order**: `{A(5.0), B(5.0), E(4.0), C(2.0), D(2.0)}` *(Note: Exact order between A and B depends on std::sort's stability, but doesn't affect this specific outcome).*
* **Allocation Loop**:
1. **A {10, 2}**: Fits. Capacity remaining: 14. Profit: 10.
2. **B {15, 3}**: Fits. Capacity remaining: 11. Profit: 25.
3. **E {8, 2}**: Fits. Capacity remaining: 9. Profit: 33.
4. **C {10, 5}**: Fits. Capacity remaining: 4. Profit: 43.
5. **D {24, 12}**: Too heavy (12 > 4). Skipped.


* **Final Output**: Profit = 43, Residue = 4.

## Practical Implications & Critical Analysis

### 1. Optimal for Fractional, Suboptimal for 0/1

This greedy algorithm based on the value-to-weight ratio is mathematically proven to yield the **absolute optimal solution** for the *Fractional* Knapsack Problem (where you are allowed to take a percentage of an item, like grain or liquid).

However, **it is suboptimal for the 0/1 Knapsack Problem** programmed here. Because items cannot be broken apart, the greedy algorithm can leave large gaps of unused capacity, trapping it in a local optimum.

**Counter-example proving suboptimality:**

* Capacity: `50`
* Items:
* Item 1: Value `60`, Weight `10` (Ratio: `6.0`)
* Item 2: Value `100`, Weight `20` (Ratio: `5.0`)
* Item 3: Value `120`, Weight `30` (Ratio: `4.0`)


* **Greedy Execution**: Sorts to `[Item 1, Item 2, Item 3]`. Takes Item 1 and Item 2. Total weight = 30, remaining capacity = 20. Item 3 (weight 30) no longer fits. **Total Profit: 160**.
* **True Optimal Solution**: Ignore Item 1. Take Item 2 and Item 3. Total weight = 50. **Total Profit: 220**.

### Key Takeaways for Application

* **Correct Algorithm Selection**: If you are solving a strict 0/1 Knapsack problem where maximizing profit is mission-critical, you **must not** use this greedy approach. You must implement a **Dynamic Programming** solution (which builds a 2D matrix of subproblems) to guarantee the optimal combination.
* **When to use Greedy**: Use this algorithm only when execution speed is vastly more important than absolute optimality, or if the items are divisible (fractional). Sorting takes $O(N \log N)$ and the loop takes $O(N)$, making it vastly faster than the pseudo-polynomial time $O(NW)$ of Dynamic Programming, especially for huge constraints.