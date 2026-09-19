#### 📋 Entendimiento del Problema

**Objetivo:** Ahora la tienda cuenta con **cantidad infinita** de cada denominación (`2, 5, 10` soles) y quiere saber la **menor cantidad de billetes** necesarios para formar un monto exacto (`meta`).

Este es el clásico **"Coin Change — mínimo número de monedas"**, pero con una variante importante en la implementación: aquí, a diferencia del problema anterior (Subset Sum, una sola vez por billete), **sí se permite repetir el mismo billete varias veces**.

```
matriz[i][j] = mínima cantidad de billetes (usando denominaciones 0..i)
               necesarios para formar exactamente el monto "j"

Sentinela "99" = "imposible" / "infinito" (nunca habrá una solución real con 99 billetes)
```

---

#### 🔍 Análisis de la Recurrencia — la clave está en el índice de fila

cpp

```cpp
if (billetes[i] <= j) {
    matriz[i][j] = min(matriz[i - 1][j], matriz[i][j - billetes[i]] + 1);
}
```

Compáralo con el problema anterior (Subset Sum):

|Problema|Fórmula al "usar" el billete|Significado|
|---|---|---|
|**Subset Sum** (1 unidad c/u)|`matriz[i-1][j - billetes[i]]`|Consumo el billete y miro la fila **anterior** (ya no puedo volver a usarlo)|
|**Este problema** (∞ unidades)|`matriz[i][j - billetes[i]] + 1`|Consumo el billete pero sigo mirando la **misma fila `i`** (puedo volver a usarlo cuantas veces quiera) y sumo 1 al conteo|

📌 **Este único cambio de índice (`i` en vez de `i-1`) es lo que convierte un problema de "0/1 knapsack" en uno de "knapsack no acotado" (suministro ilimitado).**

```
Opción A — NO usar (más) el billete i:
   heredar el mínimo ya calculado sin él → matriz[i-1][j]

Opción B — SÍ usar una unidad más del billete i:
   1 (el billete que acabo de poner) + lo que costaba formar el resto
   con billetes de tipo ≤ i (por eso es matriz[i][...], NO matriz[i-1][...])
```

##### 🚫 Caso `billetes[i] > j`

cpp

```cpp
} else {
    matriz[i][j] = matriz[i - 1][j];
}
```

Si el billete es más grande que el monto buscado, ni siquiera puedo probar usarlo → heredo directo de la fila anterior.

##### 📌 Casos base

cpp

```cpp
for (int i = 0; i <= meta; i++) matriz[0][i] = 99;   // fila del billete "0": nunca resuelve nada
for (int i = 0; i < tamanio; i++) matriz[i][0] = 0;  // monto 0 siempre necesita 0 billetes
```

⚠️ Nota el **orden**: primero se llena toda la fila 0 con `99`, y **después** se sobrescribe `matriz[i][0] = 0` para _todas_ las filas (incluida la fila 0). Así, `matriz[0][0]` termina en `0` (correcto), y `matriz[0][j>0]` se queda en `99` (correcto: sin ningún billete real, no puedo formar nada distinto de 0).

---

#### 📊 Ejecución del Algoritmo (ejemplo con `meta = 12`)

`billetes = [0, 2, 5, 10]`

##### 📐 Fila i = 0 (billete = 0)

```
j:     0   1   2   3   4   5   6   7   8   9  10  11  12
fila0: 0  99  99  99  99  99  99  99  99  99  99  99  99
```

##### 🔄 Fila i = 1 (billete = 2)

cpp

```cpp
j=2:  min(matriz[0][2]=99, matriz[1][0]+1=0+1) = 1
j=4:  min(matriz[0][4]=99, matriz[1][2]+1=1+1) = 2
j=6:  min(99, matriz[1][4]+1=2+1) = 3
j=1,3,5,7,9,11 (impares): billete=2 SÍ cabe, pero matriz[1][j-2] también es 99
      → se quedan en 99 (no se puede formar un impar solo con 2's)
```

```
j:     0   1   2   3   4   5   6   7   8   9  10  11  12
fila1: 0  99   1  99   2  99   3  99   4  99   5  99   6
```

✅ Con solo billetes de 2: se puede formar cualquier **par**, con `j/2` billetes.

##### 🔄 Fila i = 2 (billete = 5)

cpp

```cpp
j=5:  min(matriz[1][5]=99, matriz[2][0]+1=1) = 1        → 5
j=7:  min(matriz[1][7]=99, matriz[2][2]+1=1+1) = 2       → 5+2
j=9:  min(matriz[1][9]=99, matriz[2][4]+1=2+1) = 3       → 5+2+2
j=10: min(matriz[1][10]=5, matriz[2][5]+1=1+1) = 2       → 5+5  (¡mejora los 5 billetes de "2+2+2+2+2"!)
j=11: min(matriz[1][11]=99, matriz[2][6]+1=3+1) = 4       → 5+2+2+2
j=12: min(matriz[1][12]=6, matriz[2][7]+1=2+1) = 3        → 5+5+2
```

```
j:     0   1   2   3   4   5   6   7   8   9  10  11  12
fila2: 0  99   1  99   2   1   3   2   4   3   2   4   3
```

📌 Aquí se ve claramente el poder del algoritmo: en `j=10`, **combinar denominaciones da mejor resultado** (2 billetes de 5) que solo usar la denominación anterior (5 billetes de 2).

##### 🔄 Fila i = 3 (billete = 10)

cpp

```cpp
j=10: min(matriz[2][10]=2, matriz[3][0]+1=1) = 1         → 10  (¡mejor que 5+5!)
j=12: min(matriz[2][12]=3, matriz[3][2]+1=1+1) = 2        → 10+2
j=1,3: billete 10 > j → se hereda de fila2 → siguen en 99
```

```
j:     0   1   2   3   4   5   6   7   8   9  10  11  12
fila3: 0  99   1  99   2   1   3   2   4   3   1   4   2
```

---

#### 📋 Tabla DP Completa

|Billete↓ \ Monto→|0|1|2|3|4|5|6|7|8|9|10|11|12|
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|**0**|0|99|99|99|99|99|99|99|99|99|99|99|99|
|**2**|0|99|**1**|99|2|99|3|99|4|99|5|99|6|
|**5**|0|99|1|99|2|**1**|3|**2**|4|**3**|2|4|3|
|**10**|0|99|1|99|2|1|3|2|4|3|**1**|4|**2**|

---

#### ✅ Resultado final

cpp

```cpp
cout << "Cantidad minima de billetes: " << matriz[tamanio - 1][meta] << endl;
```

```
Para meta = 12 → matriz[3][12] = 2   →   10 + 2 = 12  (2 billetes) ✓
Para meta = 11 → matriz[3][11] = 4   →   5 + 2 + 2 + 2 = 11  (no hay forma con menos)
Para meta = 9  → matriz[3][9]  = 3   →   5 + 2 + 2 = 9
Para meta = 3  → matriz[3][3]  = 99  →   IMPOSIBLE (ni 2 ni 5 ni 10 combinan para dar 3)
```

---

#### 🔑 Por qué `main()` descarta a mano `meta == 1` o `meta == 3`

cpp

```cpp
if (meta == 1 or meta == 3) {
    cout << "No es posible un cambio." << endl;
}
```

Esto **no es arbitrario**: con denominaciones `{2, 5}` (coprimos entre sí, `mcd(2,5)=1`), el **Teorema de Frobenius / "Chicken McNugget"** garantiza que el mayor monto _irrepresentable_ es:

```
g(2,5) = 2·5 − 2 − 5 = 3
```

Y de hecho **todo número mayor que 3 se puede formar con combinaciones de 2 y 5** (agregar el 10 solo ayuda a _reducir_ la cantidad de billetes, nunca cambia qué montos son posibles). Por eso los únicos montos imposibles son exactamente `1` y `3` — el código "adivina" el resultado exacto del algoritmo sin necesidad de ejecutarlo, como atajo de optimización. El propio algoritmo, si se ejecutara para `meta=1` o `meta=3`, devolvería `99` de todas formas.

---

#### 💻 Detalles de implementación a notar

cpp

```cpp
int matriz[tamanio][meta + 1]{};
```

De nuevo un **VLA** (extensión de GCC, no C++ estándar), inicializado en `0` con `{}` — aunque ese `0` inicial se sobrescribe de inmediato con los bucles de `99` y de `0` en la columna/fila correspondientes.

cpp

```cpp
matriz[i][j - billetes[i]] + 1
```

Este acceso **nunca sale de rango** porque el `if (billetes[i] <= j)` garantiza `j - billetes[i] >= 0`.

⚠️ **Posible confusión con el sentinela `99`:** si en algún escenario se necesitaran más de 99 billetes para un monto muy grande, el `99` dejaría de funcionar como "infinito" y produciría un resultado incorrecto (mezclaría un conteo real con el valor "imposible"). Para los rangos típicos de esta tienda no es un problema, pero es una limitación a tener en cuenta si se generaliza el código.

---

#### ⏱️ Complejidad

```
Filas (billetes):   O(tamanio)
Columnas (montos):  O(meta)

Tiempo:   O(tamanio × meta)
Espacio:  O(tamanio × meta)
```

Misma complejidad que el problema de Subset Sum anterior, pero aquí el resultado es **un número entero (mínimo conteo)** en vez de un booleano de factibilidad.

---

#### 🎯 Resumen

| Elemento                      | Explicación                                                                                    |
| ----------------------------- | ---------------------------------------------------------------------------------------------- |
| **Problema**                  | Mínimo número de billetes para formar un monto, con suministro infinito                        |
| **Tipo de DP**                | Knapsack no acotado (Unbounded Knapsack) / Coin Change mínimo                                  |
| **Estado**                    | `matriz[i][j]` = mínimos billetes (tipos 0..i) para formar el monto `j`                        |
| **Recurrencia clave**         | `min(no usar más este billete, usar uno más del mismo tipo)`                                   |
| **Diferencia vs. Subset Sum** | Usa `matriz[i][...]` (misma fila) en vez de `matriz[i-1][...]` → permite reutilizar el billete |
| **Sentinela**                 | `99` representa "imposible / infinito"                                                         |
| **Casos imposibles**          | Solo `1` y `3` (Teorema de Frobenius para 2 y 5)                                               |
| **Ejemplo (meta=12)**         | Mínimo: **2 billetes** (10 + 2)                                                                |
| **Complejidad**               | O(tamanio × meta) tiempo y espacio                                                             |