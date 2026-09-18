### **ConjuntosPD** - Subset Sum (¿Se puede hacer el peso?)

#### 📖 ¿Qué hace?

Determina si es **posible formar exactamente un peso objetivo** usando un subconjunto de los elementos dados.

#### 🔄 Lógica paso a paso

```cpp
int verificapeso(int *paq, int peso, int n) {
    // dp[i][j] = 1 si se puede hacer peso j con primeros i elementos
    int dp[n+1][peso+1];
    
    // Base: con 0 elementos, solo se puede hacer peso 0
    for (int i=0; i<=peso; i++)
        dp[0][i] = 0;  // No se puede hacer ningún peso sin elementos
    
    for (int i=0; i<=n; i++)
        dp[i][0] = 1;  // Siempre se puede hacer peso 0 (no coger nada)
    
    // Llenar la tabla
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=peso; j++) {
            // Opción 1: No usar elemento i-1
            dp[i][j] = dp[i-1][j];
            
            // Opción 2: Usar elemento i-1 (si no ya hicimos peso j)
            if (dp[i][j]==0 && j-paq[i-1]>=0)
                dp[i][j] = dp[i-1][j-paq[i-1]];
        }
    }
}
```

#### 📊 Ejemplo: `paq = {2, 3, 4}`, `peso = 7`

```
Tabla dp (1 = posible, 0 = imposible):

       Peso→  0  1  2  3  4  5  6  7
Elem↓
  0    -      1  0  0  0  0  0  0  0
  1   (2)     1  0  1  0  0  0  0  0
  2   (3)     1  0  1  1  0  1  0  0
  3   (4)     1  0  1  1  1  1  0  1  ✓
```

**Respuesta: 1** (SÍ se puede) → 3+4=7 ✓