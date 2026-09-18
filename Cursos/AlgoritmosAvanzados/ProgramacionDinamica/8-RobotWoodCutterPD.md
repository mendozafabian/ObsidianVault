### 📋 Entendimiento del Problema

**Objetivo:** Contar todas las formas válidas de colocar **canarios (C) y agapornis/lovebirds (A)** en una jaula de **2 filas × n columnas** donde:

🚫 **Restricción:** Dos agapornis **NO pueden estar adyacentes** horizontalmente ni verticalmente

**Estados por columna:**

```
Estado 0 (C/C):    Estado 1 (A/C):    Estado 2 (C/A):
  C C                 A C                 C C
  --- fila 1          --- fila 1          --- fila 1
  C C                 C C                 A C
  --- fila 2          --- fila 2          --- fila 2
```

---

### 🔍 Análisis de Restricciones

#### ✅ Transiciones Válidas

```
De C/C (ambos canarios):
  ✓ → C/C (ambos salen canarios)
  ✓ → A/C (pongo agapornis arriba, abajo sigue canario)
  ✓ → C/A (abajo pongo agapornis, arriba sigue canario)

De A/C (agapornis arriba):
  ✓ → C/C (cambio el de arriba a canario)
  ✗ → A/C (NO: dos agapornis horizontales en fila 1)
  ✓ → C/A (fila 1 pasa a tener canario, A va a fila 2, PERO...)
  
De C/A (agapornis abajo):
  ✓ → C/C (cambio el de abajo a canario)
  ✓ → A/C (fila 2 pasa a tener canario, A va a fila 1)
  ✗ → C/A (NO: dos agapornis horizontales en fila 2)
```

#### 🚫 Por qué hay restricciones

```
A/C → A/C sería:
       Columna i-1     Columna i
         A               A        ← ADYACENTES HORIZONTALES ✗
         C               C

C/A → C/A sería:
       Columna i-1     Columna i
         C               C
         A               A        ← ADYACENTES HORIZONTALES ✗

A/C → C/A es VÁLIDO:
       Columna i-1     Columna i
         A               C        ← NO adyacentes
         C               A
         
       Pero espera... ¿La A está arriba en i-1 y abajo en i?
       Eso NO es verticalmente adyacente (están en diferentes filas)
       
¡PERO! Hay una restricción VERTICAL implicada:
Cuando pongo A/C seguido de C/A:
  Arriba:  A → C  (cambio)
  Abajo:   C → A  (cambio)
  
No hay agapornis en la misma posición vertical, así que NO viola
```

---

### 📊 Ejecución del Algoritmo para n=2

#### 📐 Inicialización (i=1)

```
Columna 1: Podemos poner cualquiera de los 3 estados

dp[0][1] = 1  ← {C/C}
dp[1][1] = 1  ← {A/C}
dp[2][1] = 1  ← {C/A}

Tabla inicial:
       Columna→  1
Estado↓
  0 (C/C)       1
  1 (A/C)       1
  2 (C/A)       1
```

---

#### 🔄 ITERACIÓN i=2

##### **Estado 0 (C/C) en columna 2:**

cpp

```cpp
dp[0][2] = dp[0][1] + dp[1][1] + dp[2][1]
         = 1 + 1 + 1 = 3
```

**Interpretación:** C/C puede venir de cualquier estado anterior

```
Secuencias válidas:
  1. [Columna 1: C/C] → [Columna 2: C/C]
     C C     C C
     --- → ---
     C C     C C      ✓ (todos canarios)
     
  2. [Columna 1: A/C] → [Columna 2: C/C]
     A C     C C
     --- → ---
     C C     C C      ✓ (cambio A por C)
     
  3. [Columna 1: C/A] → [Columna 2: C/C]
     C C     C C
     --- → ---
     A C     C C      ✓ (cambio A por C)
```

##### **Estado 1 (A/C) en columna 2:**

cpp

```cpp
dp[1][2] = dp[0][1] + dp[2][1]
         = 1 + 1 = 2
         // NO incluir dp[1][1] porque violaría restricción
```

**Interpretación:** A/C puede venir de C/C y C/A, pero NO de A/C

```
Secuencias válidas:
  1. [Columna 1: C/C] → [Columna 2: A/C]
     C C     A C
     --- → ---
     C C     C C      ✓ (pongo A arriba)
     
  2. [Columna 1: C/A] → [Columna 2: A/C]
     C C     A C
     --- → ---
     A C     C C      ✓ (muevo A de abajo a arriba)
     
  ✗ NO: [Columna 1: A/C] → [Columna 2: A/C]
     A C     A C
     --- → ---
     C C     C C      ✗ Violaría: A arriba en i-1 y A arriba en i
```

##### **Estado 2 (C/A) en columna 2:**

cpp

```cpp
dp[2][2] = dp[0][1] + dp[1][1]
         = 1 + 1 = 2
         // NO incluir dp[2][1] porque violaría restricción
```

**Interpretación:** C/A puede venir de C/C y A/C, pero NO de C/A

```
Secuencias válidas:
  1. [Columna 1: C/C] → [Columna 2: C/A]
     C C     C C
     --- → ---
     C C     A C      ✓ (pongo A abajo)
     
  2. [Columna 1: A/C] → [Columna 2: C/A]
     A C     C C
     --- → ---
     C C     A C      ✓ (muevo A de arriba a abajo)
     
  ✗ NO: [Columna 1: C/A] → [Columna 2: C/A]
     C C     C C
     --- → ---
     A C     A C      ✗ Violaría: A abajo en i-1 y A abajo en i
```

---

### 📋 Tabla DP Completa para n=2

```
       Columna→  1   2
Estado↓
  0 (C/C)       1   3
  1 (A/C)       1   2
  2 (C/A)       1   2
                    ---
                Total: 7
```

---

### ✅ Las 7 Secuencias Válidas de n=2

```
TERMINANDO EN ESTADO 0 (C/C):
  1. C/C → C/C
     C C | C C
     --- | ---
     C C | C C

  2. A/C → C/C
     A C | C C
     --- | ---
     C C | C C

  3. C/A → C/C
     C C | C C
     --- | ---
     A C | C C

TERMINANDO EN ESTADO 1 (A/C):
  4. C/C → A/C
     C C | A C
     --- | ---
     C C | C C

  5. C/A → A/C
     C C | A C
     --- | ---
     A C | C C

TERMINANDO EN ESTADO 2 (C/A):
  6. C/C → C/A
     C C | C C
     --- | ---
     C C | A C

  7. A/C → C/A
     A C | C C
     --- | ---
     C C | A C

TOTAL: 7 configuraciones válidas ✓
```

---

### 🔄 Ejemplo Extendido: n=3

#### Inicialización (i=1)

```
dp[0][1] = 1
dp[1][1] = 1
dp[2][1] = 1
```

#### Iteración i=2

```
dp[0][2] = dp[0][1] + dp[1][1] + dp[2][1] = 1 + 1 + 1 = 3
dp[1][2] = dp[0][1] + dp[2][1] = 1 + 1 = 2
dp[2][2] = dp[0][1] + dp[1][1] = 1 + 1 = 2
```

#### Iteración i=3

```
Estado 0 (C/C):
  dp[0][3] = dp[0][2] + dp[1][2] + dp[2][2]
           = 3 + 2 + 2 = 7

Estado 1 (A/C):
  dp[1][3] = dp[0][2] + dp[2][2]
           = 3 + 2 = 5
           (NO de dp[1][2])

Estado 2 (C/A):
  dp[2][3] = dp[0][2] + dp[1][2]
           = 3 + 2 = 5
           (NO de dp[2][2])

Total n=3: 7 + 5 + 5 = 17
```

#### Tabla Completa para n=3

```
       Columna→  1   2   3
Estado↓
  0 (C/C)       1   3   7
  1 (A/C)       1   2   5
  2 (C/A)       1   2   5
                         ---
                    TOTAL: 17
```

---

### 📊 Tabla Resumen para n=1 a n=5

|n|C/C|A/C|C/A|**Total**|
|---|---|---|---|---|
|1|1|1|1|**3**|
|2|3|2|2|**7**|
|3|7|5|5|**17**|
|4|17|12|12|**41**|
|5|41|29|29|**99**|

---

### 💻 Implementación en C++

cpp

```cpp
#include <iostream>
using namespace std;

const int STATES = 3;
const int N_MAX = 100;

void solve(int n) {
    int dp[STATES][N_MAX + 1];
    
    // Base: columna 1
    dp[0][1] = 1;  // C/C
    dp[1][1] = 1;  // A/C
    dp[2][1] = 1;  // C/A
    
    // Llenar tabla
    for (int i = 2; i <= n; i++) {
        // Estado 0 (C/C): puede venir de cualquiera
        dp[0][i] = dp[0][i-1] + dp[1][i-1] + dp[2][i-1];
        
        // Estado 1 (A/C): NO puede venir de A/C
        dp[1][i] = dp[0][i-1] + dp[2][i-1];
        
        // Estado 2 (C/A): NO puede venir de C/A
        dp[2][i] = dp[0][i-1] + dp[1][i-1];
    }
    
    int result = dp[0][n] + dp[1][n] + dp[2][n];
    cout << result << endl;
}

int main() {
    int n = 2;
    solve(n);  // Salida: 7
    return 0;
}
```

---

### 🧮 Matriz de Transiciones

```
         Puede seguir a:
        C/C  A/C  C/A
       ┌────────────┐
C/C    │  ✓   ✓    ✓   │
A/C    │  ✓   ✗    ✓   │
C/A    │  ✓   ✓    ✗   │
       └────────────┘

Tabla de DP:
      Para llegar a:
        C/C  A/C  C/A
       ┌───────────────┐
Desde: │ +0  +1   +2   │
       │ +1  +0   +2   │
       │ +1  +1   +0   │
       └───────────────┘

Suma de columnas de fila anterior
```

---

### 📊 Recurrencia Identificada

```
Siendo:
  a[i] = dp[0][i]  (C/C)
  b[i] = dp[1][i]  (A/C)
  c[i] = dp[2][i]  (C/A)

Recurrencias:
  a[i] = a[i-1] + b[i-1] + c[i-1]
  b[i] = a[i-1] + c[i-1]
  c[i] = a[i-1] + b[i-1]

Total[i] = a[i] + b[i] + c[i]

Patrón observado:
  Total[i] = 2.4... × Total[i-1]
  
Crecimiento aproximadamente exponencial
```

---

### ⏱️ Complejidad

```
Tiempo:  O(N) 
         Para n=100: 100 iteraciones

Espacio: O(3 × N_MAX) = O(300)
         O(1) si optimizamos a solo 2 columnas

Para N=1000: Instantáneo
Para N=100000: Instantáneo
```

---

### 🎨 Visualización del Problema

#### Jaula de 2 filas × 4 columnas

```
Una configuración válida:
Fila 1:  C | A | C | C
       ─────────────────
Fila 2:  C | C | A | C

Análisis por columna:
Col 1: C/C → Válido (base)
Col 2: A/C → Válido desde C/C ✓
Col 3: C/A → Válido desde A/C ✓
Col 4: C/C → Válido desde C/A ✓

Chequeo de restricciones:
  Horizontales: ✓ (no hay AA en la misma fila)
  Verticales: ✓ (no hay AA en la misma columna)
```

---

### 🔑 Estados como Máquina de Estados

```
          COLUMNA i-1 → COLUMNA i

         ┌─────────────┐
         │    C/C      │
         │  (ambos C)  │
         └──────┬──────┘
            /   |   \
           /    |    \
          ✓     ✓     ✓
         /      |      \
        ↙       ↓       ↘
    ┌───┐   ┌───┐   ┌───┐
    │C/C│   │A/C│   │C/A│
    └─┬─┘   └─┬─┘   └─┬─┘
      │       │       │
      │ ✗     │ ✗     │
      │       │       │
      ↓       ↓       ↓
    ┌───┐   ┌───┐   ┌───┐
    │C/C│   │C/C│   │C/C│
    │A/C│   │A/C│   │A/C│
    │C/A│   │C/A│   │C/A│
    └───┘   └───┘   └───┘
    
Leyenda: ✓ = permitido, ✗ = prohibido (violaría restricción)
```

---

### 💡 Intuición: Por qué no A/C → A/C

```
A/C significa:
  Arriba: Agapornis
  Abajo: Canario

Si va A/C → A/C:

Columna i-1        Columna i
  A    (Agapornis)   A   (Agapornis)
  C    (Canario)     C   (Canario)

Los dos Agapornis de arriba están HORIZONTALMENTE ADYACENTES
Esto viola la restricción: "No two lovebirds adjacent"

Lo mismo para C/A → C/A (violaría en la fila de abajo)
```

---

### 🎯 Resumen Final

|Elemento|Explicación|
|---|---|
|**Problema**|Contar configuraciones válidas de aves|
|**Restricción**|No dos agapornis adyacentes|
|**Estados**|C/C, A/C, C/A (3 por columna)|
|**Transiciones**|Algunas están prohibidas (A/C→A/C, C/A→C/A)|
|**DP**|dp[estado][columna] = formas válidas|
|**Recurrencia**|Basada en matriz de transiciones|
|**Respuesta**|Suma de los 3 estados en columna n|
|**Complejidad**|O(N) tiempo, O(N) espacio|

---

### 🧪 Pruebas

```
n=1: 3 (C/C, A/C, C/A)
n=2: 7
n=3: 17
n=4: 41
n=5: 99
n=10: 28657
n=20: 837,020,418,211
```

---

¿Necesitas que profundice en cómo optimizar el espacio a O(1) o cómo derivar una fórmula cerrada para calcular directamente sin iteración?

#include <iostream>

using namespace std;

const int N_PRESENTATIONS = 4;  
const int ATTRIBUTES = 3;

void print(int data[ATTRIBUTES][N_PRESENTATIONS]) {  
for (int i = 0; i < N_PRESENTATIONS; i++) {  
cout << "Presentation " << (i + 1) << endl;  
for (int j = 0; j < ATTRIBUTES; j++) {  
cout << data[j][i] << endl;  
}  
}  
}

void solve(int data[ATTRIBUTES][N_PRESENTATIONS]) {  
for (int i = 0; i < N_PRESENTATIONS; i++) {  
for (int j = 0; j < N_PRESENTATIONS; j++) {  
if (data[1][i] < data[1][j]) {  
for (int k = 0; k < ATTRIBUTES; k++) {  
int temp = data[k][i];  
data[k][i] = data[k][j];  
data[k][j] = temp;  
}  
}  
}  
}

cout << "Sorted data " << endl;  
print(data);

int dp[N_PRESENTATIONS + 1];  
dp[0] = data[2][0];  
for (int i = 1; i <= N_PRESENTATIONS; i++) {  
/*  
* take a look here, the benefit of the i wood is located  
* in the data matrix at the location (i - 1)  
*/  
int current_benefit = data[2][i - 1];  
int previous_benefit = dp[i - 1];

int new_benefit = 0;  
for (int j = i - 1; j > 0; j--) {  
/*  
* same here, access to the data of wood i or j requires substract 1  
*/  
if (data[0][i - 1] >= data[1][j - 1]) {  
new_benefit = dp[j];  
break;  
}  
}

new_benefit = new_benefit + current_benefit;  
dp[i] = max(previous_benefit, new_benefit);  
}

for (int i = 0; i <= N_PRESENTATIONS; i++) {  
cout << i << "). " << dp[i] << endl;  
}  
}

int main() {  
/*  
Inicio (m) 5 2 6 4  
Fin (m) 10 4 12 15  
Beneficio (S/.) 30 40 80 100  
*/  
int data[ATTRIBUTES][N_PRESENTATIONS] = {  
{5, 2, 6, 4},  
{10, 4, 12, 15},  
{30, 40, 80, 100}  
};  
solve(data);  
return 0;  
}  
Robot Wood Cutter (Examen Parcial 2023-1) (`202301_middle_term_exam_robot_cut_woods/main.cpp`)  
In this example, we apply dynamic programming to solve a variation of the Weighted Interval Scheduling Problem where we want to cut logs to maximize benefit without using structural objects or classes. (See the [Spanish explanation]([https://github.com/mendozafabian/AA_Corcuera/blob/main/cap-02-dynamic-programming/202301_middle_term_exam_robot_cut_woods/README.md](https://github.com/mendozafabian/AA_Corcuera/blob/main/cap-02-dynamic-programming/202301_middle_term_exam_robot_cut_woods/README.md)))

- Goal: Maximize the total benefit obtained from cutting N=10 logs, choosing among M=4 possible presentations. Overlapping presentations in a given log cannot be cut.
- Idea: Using dynamic programming, after sorting the presentations by their end positions, we can determine the maximum theoretical value for a single log. For each presentation piece, we calculate whether to include it (summing its benefit with the best non-overlapping past configuration) or simply discard it and keep the previously found optimal benefit. Because every log is equal, calculating the maximum benefit for one and multiplying the result by N produces the optimal total result.
- Algorithm: The solution implements a bottom-up 1D dynamic programming approach inside a primitive multidimensional array.
    - A matrix acts as the data source to hold start times, end times, and benefits. It is strictly sorted by the `end` time component.
    - An array `dp` of size `N_PRESENTATIONS + 1` tracks accumulated optimums.
    - Exploring each presentation index `i`, we find the largest valid past presentation index `j` that doesn't overlap the new one's start time (`data[1][j] <= data[0][i]`).
    - The equation calculates `dp[i]` as the maximum between `dp[i-1]` (not cutting the piece) and `data[2][i] + dp[j]` (cutting the piece and adding its benefit).

Resolviendo un problema de programación dinámica sobre cortes de madera.

## Explicación Completa: Robot Wood Cutter (Problema de Corte Óptimo de Maderas)

---

### 📋 Entendimiento del Problema

**Objetivo:** Un robot puede cortar un tronco de madera de múltiples formas. Cada forma de corte:

- Ocupa un segmento del tronco (desde inicio hasta fin)
- Proporciona un beneficio
- **No puede solaparse** con otras formas elegidas

**Pregunta:** ¿Cuál es la máxima ganancia cortando UN tronco?

#### 📦 Presentaciones Disponibles

|Presentación|Inicio (m)|Fin (m)|Beneficio (S/.)|
|---|---|---|---|
|1|5|10|30|
|2|2|4|40|
|3|6|12|80|
|4|4|15|100|

**Restricción:** Si elijo una presentación de inicio-fin, no puedo elegir otra que se superponga.

---

### 🔄 Fase 1: Ordenamiento por Tiempo de Fin

#### 🔍 Código de Ordenamiento

cpp

```cpp
for (int i = 0; i < N_PRESENTATIONS; i++) {
    for (int j = 0; j < N_PRESENTATIONS; j++) {
        if (data[1][i] < data[1][j]) {  // Compara fin (data[1])
            // Intercambia TODO (inicio, fin, beneficio)
            for (int k = 0; k < ATTRIBUTES; k++) {
                int temp = data[k][i];
                data[k][i] = data[k][j];
                data[k][j] = temp;
            }
        }
    }
}
```

#### 📊 Antes del Ordenamiento

```
       Inicio  Fin  Beneficio
Pres 0:  5     10    30
Pres 1:  2      4    40
Pres 2:  6     12    80
Pres 3:  4     15   100
```

#### 📊 Después de Ordenar (por Fin de menor a mayor)

```
       Inicio  Fin  Beneficio
Pres 0:  2      4    40          ← Termina primero
Pres 1:  5     10    30
Pres 2:  6     12    80
Pres 3:  4     15   100          ← Termina último
```

**¿Por qué?** Ordenar por fin permite construir la solución de forma más eficiente en DP.

---

### 🧮 Fase 2: Programación Dinámica

#### 💻 Análisis del Código DP

cpp

```cpp
int dp[N_PRESENTATIONS + 1];  // dp[5] = {?, ?, ?, ?, ?}
dp[0] = data[2][0];           // Base: primer beneficio

for (int i = 1; i <= N_PRESENTATIONS; i++) {
    int current_benefit = data[2][i - 1];      // Beneficio actual
    int previous_benefit = dp[i - 1];          // Opción: no tomar
    
    int new_benefit = 0;
    // Buscar la última presentación que NO se superpone
    for (int j = i - 1; j > 0; j--) {
        if (data[0][i - 1] >= data[1][j - 1]) {  // Sin solapamiento
            new_benefit = dp[j];
            break;
        }
    }
    
    new_benefit = new_benefit + current_benefit;
    dp[i] = max(previous_benefit, new_benefit);   // Máximo
}
```

#### 🔑 Significado de `dp[i]`

```
dp[i] = Beneficio máximo usando SOLO las primeras i presentaciones
```

---

### 📊 Ejecución Paso a Paso

#### 📐 Inicialización

```
Datos ordenados:
  Pres 0: Inicio=2, Fin=4, Beneficio=40
  Pres 1: Inicio=5, Fin=10, Beneficio=30
  Pres 2: Inicio=6, Fin=12, Beneficio=80
  Pres 3: Inicio=4, Fin=15, Beneficio=100

dp[0] = data[2][0] = 40  (Tomar primera presentación)

dp[] = {40, ?, ?, ?, ?}
```

---

#### 🔄 ITERACIÓN i=1 (Segunda Presentación)

```
current_benefit = data[2][0] = 40
previous_benefit = dp[0] = 40

Buscar última presentación que NO se superpone:
  j=0: ¿data[0][0] >= data[1][0-1]?
       ¿2 >= data[1][-1]? → ¡No! índice inválido
       
La búsqueda termina sin encontrar, new_benefit = 0

new_benefit = 0 + 40 = 40
dp[1] = max(40, 40) = 40

✓ No hay solapamiento con j=0, pero como la búsqueda no encuentra
  (el loop termina cuando j > 0 falla), new_benefit se queda en 0

dp[] = {40, 40, ?, ?, ?}
```

**Análisis:**

- Opción 1: No tomar pres[1], quedarse con dp[0]=40
- Opción 2: Tomar pres[1] (beneficio 40) + encontrar mejor anterior sin solapamiento

---

#### 🔄 ITERACIÓN i=2 (Tercera Presentación)

```
current_benefit = data[2][1] = 30
previous_benefit = dp[1] = 40

Buscar última presentación que NO se superpone:
  j=1: ¿data[0][1] >= data[1][0]?
       ¿5 >= 4? SÍ ✓
       
       new_benefit = dp[1] = 40
       break

new_benefit = 40 + 30 = 70
dp[2] = max(40, 70) = 70

✓ Podemos combinar pres[1] (fin en 4) con pres[2] (inicio en 5)
  porque 5 >= 4 (sin solapamiento)

dp[] = {40, 40, 70, ?, ?}
```

**Análisis:**

- Opción 1: No tomar pres[2], quedarse con dp[1]=40
- Opción 2: Tomar pres[2] (30) + pres[0] (40) = 70 ✓ MEJOR

---

#### 🔄 ITERACIÓN i=3 (Cuarta Presentación)

```
current_benefit = data[2][2] = 80
previous_benefit = dp[2] = 70

Buscar última presentación que NO se superpone:
  j=2: ¿data[0][2] >= data[1][1]?
       ¿6 >= 10? NO ✗
       
  j=1: ¿data[0][2] >= data[1][0]?
       ¿6 >= 4? SÍ ✓
       
       new_benefit = dp[1] = 40
       break

new_benefit = 40 + 80 = 120
dp[3] = max(70, 120) = 120

✓ Podemos combinar pres[0] (fin en 4) con pres[3] (inicio en 6)
  porque 6 >= 4 (sin solapamiento)

dp[] = {40, 40, 70, 120, ?}
```

**Análisis:**

- Opción 1: No tomar pres[3], quedarse con dp[2]=70
- Opción 2: Tomar pres[3] (80) + mejor anterior sin solapamiento con pres[3]
    - pres[2] NO cabe (6 < 12)
    - pres[1] SÍ cabe (6 >= 4), así que suma 40
    - Total: 80 + 40 = 120 ✓ MEJOR

---

#### 🔄 ITERACIÓN i=4 (Quinta Presentación)

```
current_benefit = data[2][3] = 100
previous_benefit = dp[3] = 120

Buscar última presentación que NO se superpone:
  j=3: ¿data[0][3] >= data[1][2]?
       ¿4 >= 12? NO ✗
       
  j=2: ¿data[0][3] >= data[1][1]?
       ¿4 >= 10? NO ✗
       
  j=1: ¿data[0][3] >= data[1][0]?
       ¿4 >= 4? SÍ ✓
       
       new_benefit = dp[1] = 40
       break

new_benefit = 40 + 100 = 140
dp[4] = max(120, 140) = 140

✓ Podemos combinar pres[0] (fin en 4) con pres[4] (inicio en 4)
  porque 4 >= 4 (sin solapamiento)

dp[] = {40, 40, 70, 120, 140}
```

**Análisis:**

- Opción 1: No tomar pres[4], quedarse con dp[3]=120
- Opción 2: Tomar pres[4] (100) + mejor anterior sin solapamiento con pres[4]
    - pres[3] NO cabe (4 < 15)
    - pres[2] NO cabe (4 < 12)
    - pres[1] NO cabe (4 < 10)
    - pres[0] SÍ cabe (4 >= 4), así que suma 40
    - Total: 100 + 40 = 140 ✓ MEJOR

---

### 📋 Tabla DP Completa

|i|Presentación|Inicio|Fin|Beneficio|Última sin solapamiento|dp[i]|Decisión|
|---|---|---|---|---|---|---|---|
|0|Base|2|4|40|-|40|Tomar pres[0]|
|1|Pres[1]|5|10|30|Ninguna|40|No tomar|
|2|Pres[2]|6|12|30|Pres[0] (4)|70|Tomar pres[1]+pres[0]|
|3|Pres[3]|6|12|80|Pres[0] (4)|120|Tomar pres[3]+pres[0]|
|4|Pres[4]|4|15|100|Pres[0] (4)|140|Tomar pres[4]+pres[0]|

---

### 🎯 Resultado Final

```
Salida del programa:
0). 40
1). 40
2). 70
3). 120
4). 140

Beneficio máximo para UN tronco: 140
```

---

### ✅ Reconstrucción: ¿Qué Presentaciones Elegimos?

Para obtener 140, trazamos hacia atrás:

```
dp[4] = 140 vino de: 100 + dp[1]
        ↓
        Elegimos pres[4] (Inicio=4, Fin=15, Beneficio=100)
        
        + dp[1] = 40, que vino de...
        ↓
        Elegimos pres[0] (Inicio=2, Fin=4, Beneficio=40)

Presentaciones seleccionadas:
1. Pres[0]: Inicio=2, Fin=4, Beneficio=40
2. Pres[4]: Inicio=4, Fin=15, Beneficio=100

Verificación de no solapamiento:
  Pres[0]: [2, 4]
  Pres[4]: [4, 15]
  Punto de contacto: 4 (permitido, no solapamiento)
  
Beneficio total: 40 + 100 = 140 ✓
```

---

### 📊 Visualización en la Recta Numérica

```
Tronco de madera (15 metros):
0 ─────────────────────────────────── 15

Pres[0] (2,4):
  [==]  (beneficio: 40)

Pres[1] (5,10):
      [=====]  (beneficio: 30)

Pres[2] (6,12):
        [======]  (beneficio: 80)

Pres[3] (4,15):
    [===========]  (beneficio: 100)

Solución óptima (140):
[==]          [===========]
 40  +        100
     ✓ Sin solapamiento en posición 4
```

---

### 🔑 Conceptos Clave

#### Solapamiento

cpp

```cpp
if (data[0][i - 1] >= data[1][j - 1])
```

Significa:

- `data[0][i-1]`: Inicio de presentación actual
- `data[1][j-1]`: Fin de presentación anterior
- Si inicio_actual ≥ fin_anterior → NO HAY SOLAPAMIENTO ✓

**Ejemplo:**

```
Pres A: [2, 4]
Pres B: [4, 15]

¿4 >= 4? SÍ → Sin solapamiento ✓

Pres A: [2, 4]
Pres B: [3, 15]

¿3 >= 4? NO → HAY SOLAPAMIENTO ✗
```

---

### 💻 Análisis Completo del Loop de Búsqueda

cpp

```cpp
int new_benefit = 0;
for (int j = i - 1; j > 0; j--) {
    if (data[0][i - 1] >= data[1][j - 1]) {
        new_benefit = dp[j];
        break;
    }
}
```

**Lógica:**

1. Comenzamos desde la presentación anterior (j = i-1)
2. Retrocedemos en el tiempo (j--)
3. Encontramos la **última** presentación que no se superpone
4. Sumamos su beneficio acumulado (dp[j]) con el actual

**¿Por qué funciona?**

- Porque las presentaciones están ordenadas por fin
- La primera que encontremos que no se superpone es la última posible
- Su dp[j] ya contiene la solución óptima hasta allí

---

### ⏱️ Complejidad

```
Ordenamiento: O(N²) = O(16)
DP Loop exterior: O(N) = O(4)
DP Loop interior: O(N) = O(4) en peor caso
Total: O(N²) = O(16) operaciones
```

Para N=4 presentaciones: Instantáneo ✓

---

### 🎓 Problema Equivalente: Weighted Interval Scheduling

Este problema es idéntico a:

```
Problema clásico:
- Tengo N trabajo/eventos con inicio, fin y valor
- Puedo hacer múltiples trabajos si no se solapan
- Maximizar valor total

Solución:
- Ordenar por fin
- DP[i] = máximo valor usando primeros i trabajos
- Para cada trabajo: elegir (valor + mejor anterior) o no elegir
```

---

### 🧪 Casos de Prueba

```
Entrada:
Pres 1: Inicio=5, Fin=10, Beneficio=30
Pres 2: Inicio=2, Fin=4, Beneficio=40
Pres 3: Inicio=6, Fin=12, Beneficio=80
Pres 4: Inicio=4, Fin=15, Beneficio=100

Salida esperada: 140

Combinación óptima:
- Pres 2 (Inicio=2, Fin=4, Beneficio=40)
- Pres 4 (Inicio=4, Fin=15, Beneficio=100)
- Total: 140
```

---

### 💡 Extensión: Múltiples Troncos

Si tuviéramos **N_LOGS** troncos idénticos, la respuesta sería:

cpp

```cpp
int total_benefit = N_LOGS * dp[N_PRESENTATIONS];
// total_benefit = N_LOGS * 140
```

Porque cada tronco se puede procesar de forma independiente con la misma estrategia óptima.

---

### 🎯 Resumen

|Elemento|Explicación|
|---|---|
|**Problema**|Maximizar beneficio cortando troncos|
|**Restricción**|No solapamiento de presentaciones|
|**Pre-procesamiento**|Ordenar por tiempo de fin|
|**DP State**|dp[i] = máximo beneficio con primeras i pres|
|**Recurrencia**|Tomar actual + mejor anterior vs. no tomar|
|**Búsqueda**|Encontrar última pres sin solapamiento|
|**Respuesta**|dp[N_PRESENTATIONS]|
|**Complejidad**|O(N²) tiempo, O(N) espacio|