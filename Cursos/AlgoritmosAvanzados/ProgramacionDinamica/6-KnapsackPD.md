### 📋 Entendimiento General

El programa resuelve el **problema de la mochila 0/1** usando programación dinámica.

**Problema:** Tengo una mochila con capacidad **W=5** y 4 items. Quiero maximizar el valor sin exceder el peso.

#### 📦 Items Disponibles

|Item|Peso|Valor|Valor/Peso|
|---|---|---|---|
|0|2|12|6.0|
|1|1|10|10.0 ✓|
|2|3|20|6.67|
|3|2|15|7.5|

---

### 💻 Análisis del Código

cpp

```cpp
int dp[N+1][W+1];  // Tabla de (5 x 6)
// dp[i][j] = valor máximo usando primeros i items con peso máximo j
```

#### 🔑 Inicialización

cpp

```cpp
for (int i = 0; i < N + 1; i++) {
    for (int j = 0; j < W + 1; j++) {
        dp[i][j] = 0;  // Fila 0 y columna 0 = 0 (sin items o sin capacidad)
    }
}
```

#### 🔄 Recurrencia Principal

cpp

```cpp
if (weight <= j) {
    // Opción 1: Incluir item    vs    Opción 2: No incluir
    dp[i][j] = max(dp[i-1][j],  value + dp[i-1][j - weight]);
} else {
    // No cabe, no hay opción
    dp[i][j] = dp[i-1][j];
}
```

---

### 📊 Ejecución Paso a Paso

#### 📐 Tabla Inicial (Todo 0)

```
       Capacidad→  0  1  2  3  4  5
Ítems↓
  0                0  0  0  0  0  0
  1                0  0  0  0  0  0
  2                0  0  0  0  0  0
  3                0  0  0  0  0  0
  4                0  0  0  0  0  0
```

---

### 🔄 ITEM 1 (i=1): peso=2, valor=12

```
Procesamos: weights[0]=2, values[0]=12

  j=1 (Capacidad=1):
    weight=2 > j=1 → NO CABE
    dp[1][1] = dp[0][1] = 0
    
  j=2 (Capacidad=2):
    weight=2 ≤ j=2 → CABE ✓
    Opción 1 (No tomar): dp[0][2] = 0
    Opción 2 (Tomar):    12 + dp[0][0] = 12 + 0 = 12
    dp[1][2] = max(0, 12) = 12
    
  j=3 (Capacidad=3):
    weight=2 ≤ j=3 → CABE ✓
    Opción 1 (No tomar): dp[0][3] = 0
    Opción 2 (Tomar):    12 + dp[0][1] = 12 + 0 = 12
    dp[1][3] = max(0, 12) = 12
    
  j=4 (Capacidad=4):
    weight=2 ≤ j=4 → CABE ✓
    Opción 1 (No tomar): dp[0][4] = 0
    Opción 2 (Tomar):    12 + dp[0][2] = 12 + 0 = 12
    dp[1][4] = max(0, 12) = 12
    
  j=5 (Capacidad=5):
    weight=2 ≤ j=5 → CABE ✓
    Opción 1 (No tomar): dp[0][5] = 0
    Opción 2 (Tomar):    12 + dp[0][3] = 12 + 0 = 12
    dp[1][5] = max(0, 12) = 12

       Capacidad→  0  1  2  3  4  5
Ítems↓
  0                0  0  0  0  0  0
  1                0  0 12 12 12 12  ← Item 1 cabe a partir de capacidad 2
```

---

### 🔄 ITEM 2 (i=2): peso=1, valor=10

```
Procesamos: weights[1]=1, values[1]=10

  j=1 (Capacidad=1):
    weight=1 ≤ j=1 → CABE ✓
    Opción 1 (No tomar): dp[1][1] = 0
    Opción 2 (Tomar):    10 + dp[1][0] = 10 + 0 = 10
    dp[2][1] = max(0, 10) = 10
    
  j=2 (Capacidad=2):
    weight=1 ≤ j=2 → CABE ✓
    Opción 1 (No tomar): dp[1][2] = 12
    Opción 2 (Tomar):    10 + dp[1][1] = 10 + 0 = 10
    dp[2][2] = max(12, 10) = 12
    
  j=3 (Capacidad=3):
    weight=1 ≤ j=3 → CABE ✓
    Opción 1 (No tomar): dp[1][3] = 12
    Opción 2 (Tomar):    10 + dp[1][2] = 10 + 12 = 22 ⭐
    dp[2][3] = max(12, 22) = 22
    
  j=4 (Capacidad=4):
    weight=1 ≤ j=4 → CABE ✓
    Opción 1 (No tomar): dp[1][4] = 12
    Opción 2 (Tomar):    10 + dp[1][3] = 10 + 12 = 22
    dp[2][4] = max(12, 22) = 22
    
  j=5 (Capacidad=5):
    weight=1 ≤ j=5 → CABE ✓
    Opción 1 (No tomar): dp[1][5] = 12
    Opción 2 (Tomar):    10 + dp[1][4] = 10 + 12 = 22
    dp[2][5] = max(12, 22) = 22

       Capacidad→  0  1  2  3  4  5
Ítems↓
  0                0  0  0  0  0  0
  1                0  0 12 12 12 12
  2                0 10 12 22 22 22  ← Item 2 (peso=1) muy valioso
```

---

### 🔄 ITEM 3 (i=3): peso=3, valor=20

```
Procesamos: weights[2]=3, values[2]=20

  j=1 (Capacidad=1):
    weight=3 > j=1 → NO CABE
    dp[3][1] = dp[2][1] = 10
    
  j=2 (Capacidad=2):
    weight=3 > j=2 → NO CABE
    dp[3][2] = dp[2][2] = 12
    
  j=3 (Capacidad=3):
    weight=3 ≤ j=3 → CABE ✓
    Opción 1 (No tomar): dp[2][3] = 22
    Opción 2 (Tomar):    20 + dp[2][0] = 20 + 0 = 20
    dp[3][3] = max(22, 20) = 22
    
  j=4 (Capacidad=4):
    weight=3 ≤ j=4 → CABE ✓
    Opción 1 (No tomar): dp[2][4] = 22
    Opción 2 (Tomar):    20 + dp[2][1] = 20 + 10 = 30 ⭐
    dp[3][4] = max(22, 30) = 30
    
  j=5 (Capacidad=5):
    weight=3 ≤ j=5 → CABE ✓
    Opción 1 (No tomar): dp[2][5] = 22
    Opción 2 (Tomar):    20 + dp[2][2] = 20 + 12 = 32 ⭐
    dp[3][5] = max(22, 32) = 32

       Capacidad→  0  1  2  3  4  5
Ítems↓
  0                0  0  0  0  0  0
  1                0  0 12 12 12 12
  2                0 10 12 22 22 22
  3                0 10 12 22 30 32  ← Item 3 abre nuevas posibilidades
```

---

### 🔄 ITEM 4 (i=4): peso=2, valor=15

```
Procesamos: weights[3]=2, values[3]=15

  j=1 (Capacidad=1):
    weight=2 > j=1 → NO CABE
    dp[4][1] = dp[3][1] = 10
    
  j=2 (Capacidad=2):
    weight=2 ≤ j=2 → CABE ✓
    Opción 1 (No tomar): dp[3][2] = 12
    Opción 2 (Tomar):    15 + dp[3][0] = 15 + 0 = 15 ⭐
    dp[4][2] = max(12, 15) = 15
    
  j=3 (Capacidad=3):
    weight=2 ≤ j=3 → CABE ✓
    Opción 1 (No tomar): dp[3][3] = 22
    Opción 2 (Tomar):    15 + dp[3][1] = 15 + 10 = 25 ⭐
    dp[4][3] = max(22, 25) = 25
    
  j=4 (Capacidad=4):
    weight=2 ≤ j=4 → CABE ✓
    Opción 1 (No tomar): dp[3][4] = 30
    Opción 2 (Tomar):    15 + dp[3][2] = 15 + 12 = 27
    dp[4][4] = max(30, 27) = 30
    
  j=5 (Capacidad=5):
    weight=2 ≤ j=5 → CABE ✓
    Opción 1 (No tomar): dp[3][5] = 32
    Opción 2 (Tomar):    15 + dp[3][3] = 15 + 22 = 37 ⭐
    dp[4][5] = max(32, 37) = 37

       Capacidad→  0  1  2  3  4  5
Ítems↓
  0                0  0  0  0  0  0
  1                0  0 12 12 12 12
  2                0 10 12 22 22 22
  3                0 10 12 22 30 32
  4                0 10 15 25 30 37  ← ¡VALOR MÁXIMO!
```

---

### 🎯 Resultado Final

cpp

```cpp
cout << dp[N][W] << endl;
// cout << dp[4][5] << endl;
```

**Salida:** `37`

---

### 📊 Tabla Completa Finalizada

```
        Cap→  0   1   2   3   4   5
Ítems↓
  0          0   0   0   0   0   0
  1          0   0  12  12  12  12
  2          0  10  12  22  22  22
  3          0  10  12  22  30  32
  4          0  10  15  25  30  37
                                  ↑
                           MÁXIMO (37)
```

---

### 🎓 Reconstrucción: ¿Qué Items Elegimos?

Para saber qué items se incluyeron en la solución óptima, rastreamos desde `dp[4][5]`:

```
dp[4][5] = 37

¿Vino de tomar item 4?
  15 + dp[3][3] = 15 + 22 = 37 ✓ SÍ
  
  Item 4 (peso=2, valor=15) → INCLUIDO ✓

dp[3][3] = 22

¿Vino de tomar item 3?
  20 + dp[2][0] = 20 + 0 = 20 (NO)
  dp[2][3] = 22 → NO INCLUIDO ✗
  
dp[2][3] = 22

¿Vino de tomar item 2?
  10 + dp[1][2] = 10 + 12 = 22 ✓ SÍ
  
  Item 2 (peso=1, valor=10) → INCLUIDO ✓

dp[1][2] = 12

¿Vino de tomar item 1?
  12 + dp[0][0] = 12 + 0 = 12 ✓ SÍ
  
  Item 1 (peso=2, valor=12) → INCLUIDO ✓
```

#### ✅ Solución Óptima

**Items seleccionados:**

- Item 1: peso=2, valor=12
- Item 2: peso=1, valor=10
- Item 4: peso=2, valor=15

**Verificación:**

- Peso total: 2 + 1 + 2 = **5** ✓ (exactamente la capacidad)
- Valor total: 12 + 10 + 15 = **37** ✓

---

### 📐 Estructura de la DP

```
        Capacidad ↓
Item ↓

     0   1   2   3   4   5
0    0   0   0   0   0   0   ← Sin items
1    0   ?   ?   ?   ?   ?   ← Items 0
2    0   ?   ?   ?   ?   ?   ← Items 0-1
3    0   ?   ?   ?   ?   ?   ← Items 0-2
4    0   ?   ?   ?   ?   37  ← Items 0-3 → RESPUESTA

↑
Sin capacidad
```

---

### 🔑 Decisiones Clave en Cada Paso

|Item|Peso|Valor|En Cap=5|Decisión|
|---|---|---|---|---|
|1|2|12|12|Cabe, tomar|
|2|1|10|22|Cabe + anterior = mejor|
|3|3|20|32|Cabe pero no suma mas|
|4|2|15|**37**|Cabe + combina mejor|

---

### ⏱️ Complejidad

```
Tiempo:  O(N × W) = O(4 × 5) = O(20 operaciones)
Espacio: O(N × W) = O((4+1) × (5+1)) = O(30 celdas)

Para N=100, W=1000: O(100,000) → Rápido ✓
Para N=1000, W=10000: O(10,000,000) → Aceptable
Para N=10000, W=100000: O(1,000,000,000) → Lento ⚠️
```

---

### 💡 Variantes del Problema

#### 1️⃣ Ilimitado (Unbounded Knapsack)

Cambiar: `dp[i-1][j-weight]` → `dp[i][j-weight]` (reusar item)

cpp

```cpp
dp[i][j] = max(dp[i-1][j], value + dp[i][j - weight]);
```

#### 2️⃣ Con Optimización Espacial O(W)

cpp

```cpp
int dp[W+1];  // Solo 1D en lugar de 2D

for (int i = 0; i < N; i++) {
    for (int j = W; j >= weights[i]; j--) {
        dp[j] = max(dp[j], values[i] + dp[j - weights[i]]);
    }
}
```

---

### 🎯 Resumen

|Concepto|Explicación|
|---|---|
|**dp[i][j]**|Valor máximo usando items 0...i-1 con peso ≤ j|
|**Opción 1**|No tomar item i: dp[i-1][j]|
|**Opción 2**|Tomar item i: values[i] + dp[i-1][j-weight]|
|**Recurrencia**|dp[i][j] = max(Opción1, Opción2)|
|**Base**|dp[0][j] = 0 (sin items)|
|**Respuesta**|dp[N][W]|