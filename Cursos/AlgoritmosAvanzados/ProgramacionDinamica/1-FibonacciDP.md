### 📋 Entendimiento General

El programa calcula el **número de Fibonacci**
### **VERSIÓN DINÁMICA (DP)** - Array `dp[]`

#### 🔍 Código DP

cpp

```cpp
long long dp[N + 1];
dp[0] = 0;              // Base: fib(0) = 0
dp[1] = 1;              // Base: fib(1) = 1

for (int i = 2; i <= N; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];  // Construir desde abajo
}
```

#### 📊 Ejecución Paso a Paso (N=10)

```
Inicialización:
dp[0] = 0
dp[1] = 1
dp[] = {0, 1, ?, ?, ?, ?, ?, ?, ?, ?, ?}

═══════════════════════════════════════════════════════════

ITERACIÓN i=2:
  dp[2] = dp[1] + dp[0] = 1 + 0 = 1
  dp[] = {0, 1, 1, ?, ?, ?, ?, ?, ?, ?, ?}

═══════════════════════════════════════════════════════════

ITERACIÓN i=3:
  dp[3] = dp[2] + dp[1] = 1 + 1 = 2
  dp[] = {0, 1, 1, 2, ?, ?, ?, ?, ?, ?, ?}

═══════════════════════════════════════════════════════════

ITERACIÓN i=4:
  dp[4] = dp[3] + dp[2] = 2 + 1 = 3
  dp[] = {0, 1, 1, 2, 3, ?, ?, ?, ?, ?, ?}

═══════════════════════════════════════════════════════════

ITERACIÓN i=5:
  dp[5] = dp[4] + dp[3] = 3 + 2 = 5
  dp[] = {0, 1, 1, 2, 3, 5, ?, ?, ?, ?, ?}

═══════════════════════════════════════════════════════════

ITERACIÓN i=6:
  dp[6] = dp[5] + dp[4] = 5 + 3 = 8
  dp[] = {0, 1, 1, 2, 3, 5, 8, ?, ?, ?, ?}

═══════════════════════════════════════════════════════════

ITERACIÓN i=7:
  dp[7] = dp[6] + dp[5] = 8 + 5 = 13
  dp[] = {0, 1, 1, 2, 3, 5, 8, 13, ?, ?, ?}

═══════════════════════════════════════════════════════════

ITERACIÓN i=8:
  dp[8] = dp[7] + dp[6] = 13 + 8 = 21
  dp[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, ?, ?}

═══════════════════════════════════════════════════════════

ITERACIÓN i=9:
  dp[9] = dp[8] + dp[7] = 21 + 13 = 34
  dp[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ?}

═══════════════════════════════════════════════════════════

ITERACIÓN i=10:
  dp[10] = dp[9] + dp[8] = 34 + 21 = 55
  dp[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}

✅ RESULTADO: dp[10] = 55
```

#### 📋 Tabla Completa DP

|i|Operación|dp[i]|Secuencia Fibonacci|
|---|---|---|---|
|0|Base|0|**0**|
|1|Base|1|0, **1**|
|2|1+0|1|0, 1, **1**|
|3|1+1|2|0, 1, 1, **2**|
|4|2+1|3|0, 1, 1, 2, **3**|
|5|3+2|5|0, 1, 1, 2, 3, **5**|
|6|5+3|8|0, 1, 1, 2, 3, 5, **8**|
|7|8+5|13|0, 1, 1, 2, 3, 5, 8, **13**|
|8|13+8|21|0, 1, 1, 2, 3, 5, 8, 13, **21**|
|9|21+13|34|0, 1, 1, 2, 3, 5, 8, 13, 21, **34**|
|10|34+21|55|0, 1, 1, 2, 3, 5, 8, 13, 21, 34, **55**|

---

### ⚡ Comparación de Complejidad

#### 🔴 Recursivo

```
Complejidad de tiempo:  O(2^N)  ← ¡¡Exponencial!!
Complejidad espacial:   O(N)    ← Pila de recursión

Para N=40:
  2^40 = 1,099,511,627,776 operaciones potenciales 😱
  Tiempo real: ~30-60 segundos en una computadora moderna
```

#### 🟢 Dinámico

```
Complejidad de tiempo:  O(N)    ← ¡¡Lineal!!
Complejidad espacial:   O(N)    ← Array de tamaño N

Para N=40:
  40 operaciones
  Tiempo real: < 1 milisegundo ⚡
```

#### 📊 Visualización de Diferencia

```
Tiempo de ejecución (segundos):

N=40 Recursivo:  ████████████████████ 30-60 seg
N=40 DP:         ▌ < 0.001 seg

¡¡DP es 60,000 veces más rápido!!
```

---

### 📤 Salida del Programa (N=40)

```
Fibonacci N DP: 102334155
Fibonacci N RECURSIVE: 102334155
```

⚠️ **Nota:** El método recursivo tardará mucho tiempo en completarse. Si ejecutas este programa, verás que:

- La línea `DP` se imprime instantáneamente
- La línea `RECURSIVE` tardará 30-60 segundos

---

### 🎯 Por Qué DP es Mejor

|Aspecto|Recursivo|DP|
|---|---|---|
|**Recálculos**|Millones 🔴|Cero ✓|
|**Velocidad**|O(2^N) 🐢|O(N) ⚡|
|**Memoria**|O(N) stack|O(N) array|
|**N=40**|60 segundos|< 1 ms|
|**Escalabilidad**|Imposible (N>45)|Fácil (N>1000)|

---

### 💡 Lección Clave

```
RECURSIÓN PURA:
fib(5) calcula:
  - fib(3) → 2 veces
  - fib(2) → 3 veces
  - fib(1) → 5 veces
  - fib(0) → 3 veces
  
¡¡El mismo valor se calcula MÚLTIPLES VECES!!

PROGRAMACIÓN DINÁMICA:
dp[i] se calcula UNA SOLA VEZ y se guarda
Cuando lo necesitas de nuevo, solo lo accedes del array

Resultado: 60,000x más rápido
```

---

### 🔧 Optimización Alternativa (Espacio O(1))

Si solo necesitas el último valor, puedes optimizar aún más:

cpp

```cpp
long long fib_optimizado(int N) {
    if (N <= 1) return N;
    
    long long prev2 = 0, prev1 = 1;
    for (int i = 2; i <= N; i++) {
        long long actual = prev1 + prev2;
        prev2 = prev1;
        prev1 = actual;
    }
    return prev1;
}
```