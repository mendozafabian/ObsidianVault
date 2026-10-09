#### 📋 Entendimiento del Problema

**Objetivo:** Una tienda cuenta con un conjunto de billetes/monedas, **una sola unidad de cada denominación** (no un suministro infinito), y quiere saber **qué montos exactos** puede formar combinando algunos (o todos) de esos billetes.

Para el ejemplo dado: `billetes = {0, 2, 5, 10}` (el `0` inicial es solo un "relleno" para que los índices empiecen alineados, no representa un billete real).

**Esto es el clásico problema de "Subset Sum" (suma de subconjuntos)**, no el clásico "cambio de monedas" con monedas ilimitadas — aquí **cada billete se puede usar como máximo una vez**.

```
matriz[i][j] = 1  →  SÍ es posible formar la suma "j"
                      usando solo billetes[0..i]  (cada uno 0 o 1 vez)
matriz[i][j] = 0  →  NO es posible
```

---

#### 🔍 Análisis de la Recurrencia

cpp

```cpp
if (billetes[i] <= j) {
    matriz[i][j] = max(matriz[i - 1][j], matriz[i - 1][j - billetes[i]]);
} else {
    matriz[i][j] = matriz[i - 1][j];
}
```

Para cada billete `i` y cada monto objetivo `j`, hay **dos decisiones posibles**, y se toma la mejor (`max`, que aquí funciona como un OR lógico entre 0 y 1):

```
Opción A — NO usar el billete i:
   ¿ya era posible formar "j" sin este billete?  → matriz[i-1][j]

Opción B — SÍ usar el billete i:
   ¿era posible formar "j - billetes[i]" con los billetes anteriores?
   Si sí, sumando billetes[i] llego exactamente a "j" → matriz[i-1][j - billetes[i]]

Si CUALQUIERA de las dos es posible (=1), entonces matriz[i][j] = 1
```

##### 🚫 Caso especial: `billetes[i] > j`

cpp

```cpp
} else {
    matriz[i][j] = matriz[i - 1][j];
}
```

Si el billete es más grande que el monto que quiero formar, **no puedo usarlo** (usarlo se pasaría del objetivo). Entonces heredo directamente el resultado de la fila anterior — es una versión de la "Opción A" sin siquiera evaluar la B.

##### 📌 Caso base

cpp

```cpp
for (int i = 0; i < tamanio; i++) {
    matriz[i][0] = 1;
}
```

Formar la suma **0** siempre es posible: simplemente no tomo ningún billete. Por eso toda la columna `j=0` es `1`.

La fila `i=0` (billete = 0) queda en `0` para todo `j>0`, porque el "billete 0" no ayuda a formar ningún monto positivo.

---

#### 📊 Ejecución del Algoritmo

`billetes = [0, 2, 5, 10]`, `suma total = 0+2+5+10 = 17`

##### 📐 Fila i = 0 (billete = 0)

```
j:    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
fila0:1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

##### 🔄 Fila i = 1 (billete = 2)

cpp

```cpp
j=2: matriz[1][2] = max(matriz[0][2], matriz[0][0]) = max(0, 1) = 1
j=3: matriz[1][3] = max(matriz[0][3], matriz[0][1]) = max(0, 0) = 0
... (el resto queda en 0, porque fila0 solo tiene el 1 en j=0)
```

```
j:    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
fila1:1  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

✅ Con solo el billete de 2, únicamente se puede formar **0 y 2**.

##### 🔄 Fila i = 2 (billete = 5)

cpp

```cpp
j=5: matriz[2][5] = max(matriz[1][5], matriz[1][0]) = max(0, 1) = 1   → uso el billete de 5 solo
j=7: matriz[2][7] = max(matriz[1][7], matriz[1][2]) = max(0, 1) = 1   → 5 + 2
j=2: matriz[2][2] = matriz[1][2] = 1   (billete 5 > 2, no se puede usar, se hereda)
```

```
j:    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
fila2:1  0  1  0  0  1  0  1  0  0  0  0  0  0  0  0  0  0
```

✅ Con billetes {2, 5}, se puede formar: **0, 2, 5, 7** → exactamente los subconjuntos `{}, {2}, {5}, {2+5}`.

##### 🔄 Fila i = 3 (billete = 10)

cpp

```cpp
j=10: matriz[3][10] = max(matriz[2][10], matriz[2][0])  = max(0, 1) = 1   → solo el billete de 10
j=12: matriz[3][12] = max(matriz[2][12], matriz[2][2])  = max(0, 1) = 1   → 10 + 2
j=15: matriz[3][15] = max(matriz[2][15], matriz[2][5])  = max(0, 1) = 1   → 10 + 5
j=17: matriz[3][17] = max(matriz[2][17], matriz[2][7])  = max(0, 1) = 1   → 10 + 5 + 2
j=2,5,7: se heredan de la fila anterior (billete 10 > esos montos)
```

```
j:    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
fila3:1  0  1  0  0  1  0  1  0  0  1  0  1  0  0  1  0  1
```

---

#### 📋 Tabla DP Completa

|Billete↓ \ Monto→|0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|**0**|1|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
|**2**|1|0|**1**|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
|**5**|1|0|1|0|0|**1**|0|**1**|0|0|0|0|0|0|0|0|0|0|
|**10**|1|0|1|0|0|1|0|1|0|0|**1**|0|**1**|0|0|**1**|0|**1**|

---

#### ✅ Resultado final

cpp

```cpp
cout << "Se puede dar cambio para: ";
for (int i = 1; i <= suma; i++) {
    if (matriz[tamanio - 1][i] == 1) {
        cout << setw(5) << i;
    }
}
```

Recorre la **última fila** (la que ya considera _todos_ los billetes disponibles) y muestra cada monto marcado con `1`:

```
Se puede dar cambio para:  2   5   7  10  12  15  17
```

Que corresponden exactamente a **todas las sumas posibles** de subconjuntos de `{2, 5, 10}`:

```
{}         = 0   (no se muestra, no es cambio útil)
{2}        = 2
{5}        = 5
{2,5}      = 7
{10}       = 10
{2,10}     = 12
{5,10}     = 15
{2,5,10}   = 17
```

---

#### 🔑 Diferencia clave con "cambio de monedas" clásico

|Aspecto|Este algoritmo (Subset Sum)|Cambio de monedas clásico|
|---|---|---|
|**Uso de cada denominación**|Como máximo **una vez**|Ilimitado|
|**Transición**|`max(no usar, usar)` → 0/1|Suele sumar combinaciones (`+=`)|
|**Pregunta que responde**|¿Es posible formar el monto?|¿Cuántas formas hay de formar el monto?|
|**Analogía real**|La tienda tiene **un** billete de 2, **un** billete de 5, **un** billete de 10|Una caja registradora con muchas monedas de cada tipo|

Esto tiene sentido con el enunciado: _"con un conjunto limitado de monedas con las que cuenta"_ — son piezas físicas específicas, no un suministro infinito.

---

#### 💻 Detalles de implementación a notar

cpp

```cpp
int matriz[tamanio][suma + 1]{};
```

Es un **VLA (variable-length array)** — su tamaño se define en tiempo de ejecución con `tamanio` y `suma`. No es C++ estándar (es una extensión de GCC), pero funciona en la práctica. El `{}` al final inicializa todo en `0`.

cpp

```cpp
int max(int a, int b) { ... }
```

Se define una función `max` propia, que **oculta** (shadow) a `std::max` — funciona igual pero es redundante dado el `using namespace std;`.

La función `imprimir(int *matriz[], ...)` está declarada pero **nunca se usa** en `main()` — es código muerto que recibía un arreglo de punteros (`int*[]`), un tipo distinto al `int matriz[][]` real usado en `calcular`, así que ni siquiera sería compatible si se llamara.

---

#### ⏱️ Complejidad

```
Filas (billetes):      O(tamanio)
Columnas (montos):     O(suma)

Tiempo:   O(tamanio × suma)
Espacio:  O(tamanio × suma)   (podría optimizarse a O(suma) con una sola fila, 
                                iterando j de mayor a menor)
```

Para el ejemplo (`tamanio=4`, `suma=17`), son apenas ~68 celdas — instantáneo.

---

#### 🎯 Resumen

| Elemento                 | Explicación                                                                  |
| ------------------------ | ---------------------------------------------------------------------------- |
| **Problema**             | Determinar qué montos se pueden formar con un billete de cada denominación   |
| **Tipo de DP**           | Subset Sum (0/1 knapsack booleano)                                           |
| **Estado**               | `matriz[i][j]` = ¿es posible formar el monto `j` usando los billetes `0..i`? |
| **Recurrencia**          | `max(no usar el billete, usarlo si cabe)`                                    |
| **Caso base**            | `matriz[i][0] = 1` (el monto 0 siempre se puede formar)                      |
| **Resultado**            | Última fila: todas las posiciones `j` con valor `1`                          |
| **Salida para {2,5,10}** | 2, 5, 7, 10, 12, 15, 17                                                      |
| **Complejidad**          | O(tamanio × suma) tiempo y espacio                                           |