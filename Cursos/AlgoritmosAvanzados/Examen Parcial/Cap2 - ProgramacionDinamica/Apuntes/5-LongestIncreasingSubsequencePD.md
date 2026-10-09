### 📋 Entendimiento General

El programa calcula la **Subsecuencia Creciente Más Larga (LIS)** en un arreglo.

**Array:** `X[] = {-7, 1, 9, 8, 3, 8, 10, 1}`

**Objetivo:** Encontrar la longitud de la secuencia más larga donde cada número es **mayor que el anterior**.

---

### 🔍 Concepto de LIS

#### Ejemplos de Subsecuencias Crecientes:

```
{-7, 1, 9}        → Longitud: 3
{-7, 1, 8, 10}    → Longitud: 4  ✓ LIS
{-7, 1, 3, 8, 10} → Longitud: 5  ✓ LIS MÁXIMA
{1, 9, 10}        → Longitud: 3
{-7, 1}           → Longitud: 2
```

⚠️ **Nota:** No tiene que ser contigua, solo que mantenga el orden creciente.

---

### 💻 Análisis del Código

cpp

```cpp
int X[] = {-7, 1, 9, 8, 3, 8, 10, 1};
int dp[N] = {1};  // Inicializa todo en 1 (cada elemento es LIS de tamaño 1)

// dp[i] = longitud de la LIS que termina en X[i]
```

#### 🔑 Lógica Principal

cpp

```cpp
for (int i = 1; i < N; i++) {                    // Para cada posición
    for (int j = 0; j < i; j++) {                // Mirar todos anteriores
        if (X[i] > X[j]) {                       // Si es mayor
            dp[i] = max(dp[j] + 1, dp[i]);       // Extender LIS
        }
    }
}
```

**Idea:** Si encuentro un elemento anterior más pequeño, puedo extender su LIS.

---

### 📊 Ejecución Paso a Paso

#### Inicialización

```
X[]  = {-7,  1,  9,  8,  3,  8, 10,  1}
Índice: 0   1   2   3   4   5   6   7

dp[] = {1,  1,  1,  1,  1,  1,  1,  1}
       ↑ Inicialmente cada elemento forma LIS de longitud 1
```

---

#### 🔄 ITERACIÓN i=1 (X[1]=1)

```
Buscamos si hay algún X[j] < X[1] donde j < 1

  j=0: X[0]=-7 < X[1]=1 ✓
       dp[1] = max(dp[0]+1, dp[1]) = max(1+1, 1) = 2
       
Estado: dp = {1, 2, 1, 1, 1, 1, 1, 1}

✓ LIS terminando en índice 1: {-7, 1}
```

---

#### 🔄 ITERACIÓN i=2 (X[2]=9)

```
Buscamos si hay algún X[j] < X[2] donde j < 2

  j=0: X[0]=-7 < X[2]=9 ✓
       dp[2] = max(dp[0]+1, dp[2]) = max(1+1, 1) = 2
       
  j=1: X[1]=1 < X[2]=9 ✓
       dp[2] = max(dp[1]+1, dp[2]) = max(2+1, 2) = 3
       
Estado: dp = {1, 2, 3, 1, 1, 1, 1, 1}

✓ LIS terminando en índice 2: {-7, 1, 9}
```

---

#### 🔄 ITERACIÓN i=3 (X[3]=8)

```
Buscamos si hay algún X[j] < X[3] donde j < 3

  j=0: X[0]=-7 < X[3]=8 ✓
       dp[3] = max(dp[0]+1, dp[3]) = max(1+1, 1) = 2
       
  j=1: X[1]=1 < X[3]=8 ✓
       dp[3] = max(dp[1]+1, dp[3]) = max(2+1, 2) = 3
       
  j=2: X[2]=9 > X[3]=8 ✗
       No se actualiza
       
Estado: dp = {1, 2, 3, 3, 1, 1, 1, 1}

✓ LIS terminando en índice 3: {-7, 1, 8}
```

---

#### 🔄 ITERACIÓN i=4 (X[4]=3)

```
Buscamos si hay algún X[j] < X[4] donde j < 4

  j=0: X[0]=-7 < X[4]=3 ✓
       dp[4] = max(dp[0]+1, dp[4]) = max(1+1, 1) = 2
       
  j=1: X[1]=1 < X[4]=3 ✓
       dp[4] = max(dp[1]+1, dp[4]) = max(2+1, 2) = 3
       
  j=2: X[2]=9 > X[4]=3 ✗
       No se actualiza
       
  j=3: X[3]=8 > X[4]=3 ✗
       No se actualiza
       
Estado: dp = {1, 2, 3, 3, 3, 1, 1, 1}

✓ LIS terminando en índice 4: {-7, 1, 3}
```

---

#### 🔄 ITERACIÓN i=5 (X[5]=8)

```
Buscamos si hay algún X[j] < X[5] donde j < 5

  j=0: X[0]=-7 < X[5]=8 ✓
       dp[5] = max(dp[0]+1, dp[5]) = max(1+1, 1) = 2
       
  j=1: X[1]=1 < X[5]=8 ✓
       dp[5] = max(dp[1]+1, dp[5]) = max(2+1, 2) = 3
       
  j=2: X[2]=9 > X[5]=8 ✗
       
  j=3: X[3]=8 = X[5]=8 ✗ (No es estrictamente menor)
       
  j=4: X[4]=3 < X[5]=8 ✓
       dp[5] = max(dp[4]+1, dp[5]) = max(3+1, 3) = 4
       
Estado: dp = {1, 2, 3, 3, 3, 4, 1, 1}

✓ LIS terminando en índice 5: {-7, 1, 3, 8}
```

---

#### 🔄 ITERACIÓN i=6 (X[6]=10)

```
Buscamos si hay algún X[j] < X[6] donde j < 6

  j=0: X[0]=-7 < X[6]=10 ✓
       dp[6] = max(dp[0]+1, dp[6]) = max(1+1, 1) = 2
       
  j=1: X[1]=1 < X[6]=10 ✓
       dp[6] = max(dp[1]+1, dp[6]) = max(2+1, 2) = 3
       
  j=2: X[2]=9 < X[6]=10 ✓
       dp[6] = max(dp[2]+1, dp[6]) = max(3+1, 3) = 4
       
  j=3: X[3]=8 < X[6]=10 ✓
       dp[6] = max(dp[3]+1, dp[6]) = max(3+1, 4) = 4
       
  j=4: X[4]=3 < X[6]=10 ✓
       dp[6] = max(dp[4]+1, dp[6]) = max(3+1, 4) = 4
       
  j=5: X[5]=8 < X[6]=10 ✓
       dp[6] = max(dp[5]+1, dp[6]) = max(4+1, 4) = 5 ⭐
       
Estado: dp = {1, 2, 3, 3, 3, 4, 5, 1}

✓ LIS terminando en índice 6: {-7, 1, 3, 8, 10}
```

---

#### 🔄 ITERACIÓN i=7 (X[7]=1)

```
Buscamos si hay algún X[j] < X[7] donde j < 7

  j=0: X[0]=-7 < X[7]=1 ✓
       dp[7] = max(dp[0]+1, dp[7]) = max(1+1, 1) = 2
       
  j=1: X[1]=1 = X[7]=1 ✗ (No es estrictamente menor)
       
  j=2: X[2]=9 > X[7]=1 ✗
  j=3: X[3]=8 > X[7]=1 ✗
  j=4: X[4]=3 > X[7]=1 ✗
  j=5: X[5]=8 > X[7]=1 ✗
  j=6: X[6]=10 > X[7]=1 ✗
       
Estado: dp = {1, 2, 3, 3, 3, 4, 5, 2}

✓ LIS terminando en índice 7: {-7, 1}
```

---

### 📋 Tabla Resumen Completa

|i|X[i]|dp[i]|Decisión|LIS que termina aquí|
|---|---|---|---|---|
|0|-7|1|Base|{-7}|
|1|1|2|Extiende desde dp[0]|{-7, 1}|
|2|9|3|Extiende desde dp[1]|{-7, 1, 9}|
|3|8|3|Extiende desde dp[1]|{-7, 1, 8}|
|4|3|3|Extiende desde dp[1]|{-7, 1, 3}|
|5|8|4|Extiende desde dp[4]|{-7, 1, 3, 8}|
|6|10|**5**|Extiende desde dp[5]|**{-7, 1, 3, 8, 10}**|
|7|1|2|Extiende desde dp[0]|{-7, 1}|

---

### 🎯 Resultado Final

cpp

```cpp
int max_value = 0;
for (int i = 0; i < N; i++) {
    max_value = max(max_value, dp[i]);
}
// max_value = max(1, 2, 3, 3, 3, 4, 5, 2) = 5
```

**Salida:** `5`

---

### 📊 Visualización Gráfica

```
X[]  = {-7,  1,  9,  8,  3,  8, 10,  1}
dp[] = { 1,  2,  3,  3,  3,  4,  5,  2}
                                 ↑
                           MÁXIMO (5)

LIS = {-7 → 1 → 3 → 8 → 10}
      Longitud: 5 elementos
```

---

### 🔄 Resumen de la Lógica

```
Para cada posición i:
  1. Miro todos los elementos anteriores j
  2. Si X[j] < X[i], puedo extender su LIS
  3. Tomo la extensión más larga: dp[i] = max(dp[j]+1)
  
Resultado: El máximo valor en dp[]
```

---

### ⏱️ Complejidad

```
Tiempo:  O(N²)   ← Dos bucles anidados
Espacio: O(N)    ← Array dp de tamaño N

Para N=8:  8×8 = 64 comparaciones
Para N=1000: 1,000,000 comparaciones (aceptable)
```

---

### 💡 Alternativas Mejores

Si N es muy grande (>100,000), existe **Binary Search + DP** con O(N log N):

cpp

```cpp
// Más eficiente pero más complejo
// Usa búsqueda binaria en lugar de búsqueda lineal
```

---

### 🎓 Lecciones Clave

|Concepto|Explicación|
|---|---|
|**Subsecuencia**|No tiene que ser contigua|
|**Creciente**|Cada elemento > anterior|
|**dp[i]**|LIS que **termina** en posición i|
|**Recurrencia**|dp[i] = max(dp[j]+1) si X[i]>X[j]|
|**Respuesta**|max(dp[0]...dp[N-1])|

---

### 🔧 Modificaciones Posibles

#### 1️⃣ Encontrar la secuencia (no solo longitud)

cpp

```cpp
int parent[N] = {-1};  // Guardar índice anterior

for (int i = 1; i < N; i++) {
    for (int j = 0; j < i; j++) {
        if (X[i] > X[j] && dp[j]+1 > dp[i]) {
            dp[i] = dp[j] + 1;
            parent[i] = j;  // Guardar de dónde vinimos
        }
    }
}

// Reconstruir la secuencia
int idx = 6;  // índice con máximo
while (idx != -1) {
    cout << X[idx] << " ";
    idx = parent[idx];
}
```

#### 2️⃣ LIS No Decreciente (≥ en lugar de >)

cpp

```cpp
if (X[i] >= X[j]) {  // Cambiar > por >=
    dp[i] = max(dp[j] + 1, dp[i]);
}
```