# Greedy Algorithm: Multiple Bin Packing (Truck Loading)

## Core Summary

This C++ code implements a heuristic solution to a variation of the **Multiple Knapsack** or **Bin Packing Problem**. The objective is to allocate a set of items (packages) into a set of containers (trucks) with distinct capacities. The script uses a greedy approach similar to the **First Fit Decreasing (FFD)** algorithm: it sorts the packages from largest to smallest, sorts the trucks from smallest to largest initial capacity, and then iteratively assigns each package to the first available truck that can accommodate its weight.

  

## Key Concepts & Definitions

- **Bin Packing Problem**: A classic combinatorial optimization problem where items of different volumes/weights must be packed into a finite number of bins (trucks) in a way that minimizes the number of bins used or maximizes the space utilized. It is NP-hard.
    
      
    
- **First Fit Decreasing (FFD) Heuristic**: A greedy strategy that sorts items in descending order of size before attempting to place them. FFD significantly improves packing efficiency compared to random ordering because it handles the hardest-to-place (largest) items first.
    
      
    
- **Struct Reusability**: The code uses a single `struct Tobejto` to model two conceptually different domain entities (Packages and Trucks) because they share the same data structure (an ID and a quantity/capacity).
    
      
    

## Detailed Breakdown of the Code

### 1. Data Structures

C++

```
struct Tobejto { int id; int cant; };
struct Tresultado { int idCamion; int idPaquete; };
```

- `Tobejto` (Object) acts as a generic container holding an identifier and a magnitude (`cant`).
    
      
    
- `Tresultado` records the many-to-many resolution, pairing a specific truck ID with a specific package ID.
    
      
    

### 2. Sorting Phase

C++

```
sort(paquetes.begin(), paquetes.end(), gt); // Descending
sort(camiones.begin(), camiones.end(), lt); // Ascending
```

- **Packages** are sorted descending (`gt`). This ensures the algorithm tries to pack the most restrictive elements first.
    
      
    
- **Trucks** are sorted ascending (`lt`). The intention here is to preserve the larger trucks for larger packages by attempting to fill the smaller trucks first, minimizing wasted space in large containers.
    
      
    

### 3. Allocation Logic (The Greedy Search)

C++

```
for (int i = 0; i < paquetes.size(); i++) {
    for (int j = 0; j < camiones.size(); j++) {
        if (camiones[j].cant >= paquetes[i].cant) {
            camiones[j].cant -= paquetes[i].cant;
            resultados.push_back({camiones[j].id, paquetes[i].id});
            break; 
        }
    }
}
```

- For each package, the algorithm linearly scans the truck array.
    
      
    
- When a truck with sufficient remaining capacity (`camiones[j].cant >= paquetes[i].cant`) is found, the package is assigned.
    
      
    
- The truck's capacity is immediately decremented by the package's weight.
    
      
    
- The `break` statement is critical: it halts the inner loop so a single package is not duplicated across multiple trucks, moving execution to the next package.
    
      
    

## Practical Implications & Critical Analysis

### Algorithmic Limitations and Edge Cases

1. **State Degradation (Not "Best Fit")**: Because the trucks are only sorted _once_ at the beginning, the array loses its strict ascending order as soon as a package is loaded. The algorithm behaves as First Fit over a statically ordered list, rather than dynamically finding the "Best Fit" (the truck with the tightest remaining capacity). To maintain a true Best Fit strategy, the trucks would need to be re-sorted or managed in a priority queue after every insertion.
    
      
    
2. **Unallocated Packages**: The current logic silently drops packages if they do not fit into any truck. In a production environment, there must be error handling or an "unassigned" array to track packages that failed the allocation loop.
    
      
    
3. **Time Complexity**: The sorting phase takes $O(P \log P + T \log T)$ where $P$ is the number of packages and $T$ is the number of trucks. The nested allocation loop is $O(P \times T)$ in the worst case (if every package has to check every truck). This quadratic time complexity is acceptable for small inputs but scales poorly for massive logistics datasets.
    
      
    

### Code Design / Maintainability

While reusing `Tobejto` for both packages and trucks reduces lines of code, it is an anti-pattern in **Domain-Driven Design**. A package's `cant` represents _weight_, while a truck's `cant` represents _capacity_. If the system scales (e.g., packages gain a `fragile` boolean, or trucks gain a `refrigerated` boolean), this shared struct will force unnecessary fields on both entities. It is strictly better for maintainability to define `struct Paquete` and `struct Camion` separately, even if their initial fields are identical.