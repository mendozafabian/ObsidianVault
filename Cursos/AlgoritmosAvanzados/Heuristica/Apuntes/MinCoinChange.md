# Greedy Algorithm: Minimum Coin Change (C++)

## Core Summary

This C++ code implements a **greedy algorithm** to solve the **Coin Change Problem**. The objective is to make change for a specific amount (`cambioRestante`) using the absolute minimum number of coins. The heuristic achieves this by sorting the available coin denominations in descending order and iteratively taking the largest possible denomination that does not exceed the remaining target amount.

## Key Concepts & Definitions

* **Coin Change Problem**: A classic algorithmic problem asking for the minimum number of coins of given denominations needed to make a specific sum.
* **Canonical Coin Systems**: A system of coin denominations where the greedy algorithm is mathematically guaranteed to always yield the globally optimal solution (minimum coins). Most real-world currencies (like USD, Euros, or Peruvian Soles) are canonical.
* **Unbounded Knapsack Variation**: Unlike the 0/1 Knapsack problem where items can only be used once, this algorithm allows a single coin denomination to be used multiple times until the remaining change is smaller than that denomination.

## Detailed Breakdown of the Code

### 1. Pre-processing (Sorting)

```cpp
sort(denominaciones.begin(), denominaciones.end(), gt);

```

The algorithm strictly requires the coins to be checked from largest to smallest. The `std::sort` function, combined with the custom `gt` (greater than) comparator, ensures the array is evaluated in descending order (e.g., `50, 20, 10, 5, 2, 1`).

### 2. The Greedy Loop Logic

```cpp
while (i < denominaciones.size() and cambioRestante > 0) {
    if (cambioRestante >= denominaciones[i]) {
        // ... subtract coin value, increment counter
    } else {
        i++;
    }
}

```

* The loop continues as long as there are denominations left to check and the target amount (`cambioRestante`) has not reached zero.
* **Reuse Mechanism**: If a coin fits (`cambioRestante >= denominaciones[i]`), its value is subtracted, but the index `i` is **not incremented**. This is crucial; it allows the algorithm to use the same large denomination multiple times (e.g., using two `2` coins to make `4`).
* **Progression**: The index `i` is only incremented when the current denomination is strictly larger than the remaining change, forcing the algorithm to evaluate the next smaller coin.

### 3. Execution Trace (Based on `main`)

* **Target Amount**: 19
* **Sorted Denominations**: `{50, 20, 10, 5, 2, 1}`
* **Trace**:
* 50: Too large. (`i++`)
* 20: Too large. (`i++`)
* 10: Fits. Remainder = 9. Coins = 1. (Keep checking 10).
* 10: Too large for 9. (`i++`)
* 5: Fits. Remainder = 4. Coins = 2. (Keep checking 5).
* 5: Too large for 4. (`i++`)
* 2: Fits. Remainder = 2. Coins = 3. (Keep checking 2).
* 2: Fits. Remainder = 0. Coins = 4.


* **Result**: 4 coins used (10, 5, 2, 2). Residue: 0.

## Critical Analysis & Practical Implications

### 1. The "Non-Canonical" Failure Case

The greedy approach works perfectly for the provided denominations `{1, 2, 5, 10, 20, 50}`. However, it completely fails to find the optimal solution for **non-canonical** denomination sets.

**Counter-example:**

* Denominations: `{1, 3, 4}`
* Target Amount: `6`
* **Greedy output**: Takes `4`. Remainder `2`. Takes `1`. Remainder `1`. Takes `1`. Total coins: **3** (4 + 1 + 1).
* **Optimal output**: Take two `3` coins. Total coins: **2** (3 + 3).

### 2. The "No Solution" Edge Case

If the denomination set does not include a `1` and cannot perfectly sum to the target amount, the algorithm will finish with a `cambioRestante > 0` but will not explicitly throw an error or backtrack to try other combinations. For instance, with denominations `{2, 5}` and a target of `3`, the greedy algorithm takes `2`, leaves a remainder of `1`, and stops, failing to provide exact change.

### Key Takeaways for Application

* **When to use**: This algorithm is extremely fast ($O(N \log N)$ for sorting, $O(M)$ for the loop where M is the final number of coins). It is the correct choice for standard, real-world monetary systems.
* **When to avoid**: If the system allows arbitrary, non-canonical coin denominations, you cannot rely on this greedy heuristic. You must implement a **Dynamic Programming** solution (specifically, the Unbounded Knapsack/Coin Change DP approach) to guarantee the minimum number of coins.