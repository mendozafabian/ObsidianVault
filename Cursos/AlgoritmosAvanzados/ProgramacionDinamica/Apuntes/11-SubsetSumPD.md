
#### 📋 Entendimiento del Problema

**Contexto:** Una tienda cuenta con **un billete/moneda de cada denominación**: uno de 2 soles, uno de 5 soles y uno de 10 soles (el `0` inicial en el arreglo es un valor "relleno", no una moneda real — ya lo veremos).

**Objetivo:** Determinar **todos los montos de cambio** que la tienda puede entregar combinando, sin repetir, las monedas que tiene disponibles.

🚫 **Restricción clave (a diferencia del clásico "coin change"):** cada moneda se puede usar **como máximo una vez**, porque solo hay una de cada denominación. Esto convierte el problema en un **subset-sum / mochila 0/1**, no en un "cambio con monedas ilimitadas".

```
Monedas disponibles: 2, 5, 10 soles
Pregunta: ¿qué sumas (0, 1, 2, 3, ... hasta 17) se pueden formar
          eligiendo un SUBCONJUNTO de {2, 5, 10}?
```

---

#### 🔍 Análisis del Código

##### 🧩 El significado de `matriz[i][j]`

```
matriz[i][j] = 1  →  SÍ se puede formar la suma "j"
                      usando solo las monedas billetes[0..i]
matriz[i][j] = 0  →  NO se puede formar esa suma
```

- **Filas (`i`)**: qué monedas están "disponibles para usar" (desde `billetes[0]` hasta `billetes[i]`).
- **Columnas (`j`)**: el monto objetivo, de `0` hasta `suma` (la suma total de todas las monedas = 17).

##### 🔑 Por qué `billetes[0] = 0`

cpp

```cpp
int billetes[]{0,2,5,10};
```

El `0` es un **billete ficticio (sentinel)**. Sirve para que la fila `i=0` represente "el caso sin ninguna moneda real todavía":

cpp

```cpp
for (int i = 0; i < tamanio; i++) {
    matriz[i][0] = 1;   // con 0 monedas, siempre se puede formar la suma 0
}
```

Como el bucle principal empieza en `i = 1`, la fila 0 **nunca se recalcula** — se queda como "solo la suma 0 es alcanzable", que es el caso base correcto antes de considerar la primera moneda real (2 soles).

##### ✅ La recurrencia (mochila 0/1)

cpp

```cpp
if (billetes[i] <= j) {
    matriz[i][j] = max(matriz[i-1][j], matriz[i-1][j-billetes[i]]);
} else {
    matriz[i][j] = matriz[i-1][j];
}
```

Para cada monto `j`, hay dos decisiones posibles con la moneda `billetes[i]`:

```
NO usar billetes[i]  →  matriz[i-1][j]              (igual que sin esta moneda)
SÍ usar billetes[i]  →  matriz[i-1][j - billetes[i]] (el resto lo forman las anteriores)

Como buscamos "¿es POSIBLE?" (0 o 1), usamos max() en vez de sumar:
si CUALQUIERA de las dos opciones da 1 → matriz[i][j] = 1
```

Esto es exactamente la misma idea del "Weighted Interval Scheduling" que vimos antes (tomar vs. no tomar), pero aquí la "ganancia" no es un beneficio sino un booleano de factibilidad.

---

#### 📊 Ejecución Paso a Paso

`billetes = {0, 2, 5, 10}`, `tamanio = 4`, `suma = 0+2+5+10 = 17` → matriz de `4 × 18`.

##### 📐 Inicialización

```
matriz[0][0] = 1
matriz[1][0] = 1
matriz[2][0] = 1
matriz[3][0] = 1
(resto de la fila 0 se queda en 0, nunca se toca)
```

##### 🔄 Fila i=1 (billetes[1] = 2)

cpp

```cpp
j=1: 2<=1? NO  → matriz[1][1] = matriz[0][1] = 0
j=2: 2<=2? SÍ  → max(matriz[0][2], matriz[0][0]) = max(0,1) = 1
j=3..17: max(matriz[0][j], matriz[0][j-2]) = 0  (fila 0 solo tiene el 1 en col 0)
```

**Resultado fila 1:** solo `0` y `2` son alcanzables (obvio: con una sola moneda de 2, o nada).

```
Fila 1:  1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
col:     0 1 2 3 4 5 6 7 8 9 ...
```

##### 🔄 Fila i=2 (billetes[2] = 5)

cpp

```cpp
j=5: max(matriz[1][5], matriz[1][0]) = max(0,1) = 1   → "solo el 5"
j=7: max(matriz[1][7], matriz[1][2]) = max(0,1) = 1   → "5 + 2"
resto: se copia de la fila 1 o queda en 0
```

```
Fila 2:  1 0 1 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0
col:     0 1 2 3 4 5 6 7 8 9 ...
```

**Interpretación:** con {2, 5} disponibles, los montos posibles son `0, 2, 5, 7`.

##### 🔄 Fila i=3 (billetes[3] = 10)

cpp

```cpp
j=10: max(matriz[2][10], matriz[2][0]) = max(0,1) = 1   → "solo el 10"
j=12: max(matriz[2][12], matriz[2][2]) = max(0,1) = 1   → "10 + 2"
j=15: max(matriz[2][15], matriz[2][5]) = max(0,1) = 1   → "10 + 5"
j=17: max(matriz[2][17], matriz[2][7]) = max(0,1) = 1   → "10 + 5 + 2"
resto: copiado de fila 2 (para j=1..9) o 0
```

```
Fila 3:  1 0 1 0 0 1 0 1 0 0 1 0  1  0  0  1  0  1
col:     0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17
```

---

#### 📋 Tabla DP Completa (tal como la imprime `imprimir`/el `cout` final)

|Fila (monedas usadas hasta)|0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|i=0 (solo el "0")|1|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
|i=1 (+2)|1|0|1|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
|i=2 (+5)|1|0|1|0|0|1|0|1|0|0|0|0|0|0|0|0|0|0|
|i=3 (+10)|1|0|1|0|0|1|0|1|0|0|1|0|1|0|0|1|0|1|

**Los "1" de la última fila indican exactamente qué subconjunto de {2,5,10} los produce:**

|Monto|Subconjunto que lo forma|
|---|---|
|0|{} (nada)|
|2|{2}|
|5|{5}|
|7|{2, 5}|
|10|{10}|
|12|{2, 10}|
|15|{5, 10}|
|17|{2, 5, 10}|

---

#### ⚠️ El detalle (bug/decisión de diseño) en la impresión final

cpp

```cpp
for (int i = 0; i < suma; i++) {          // i va de 0 a 16, NUNCA llega a 17
    if (matriz[tamanio-1][i] == 1) {
        cout << setw(5) << i;
    }
}
```

Como la condición es `i < suma` (con `suma = 17`), el bucle recorre `0..16` pero **excluye el 17**, que sí es técnicamente alcanzable (`matriz[3][17] = 1`).

```
Salida real del programa:  0   2   5   7   10   12   15
                                                         ↑
                                            el 17 NO se imprime, aunque es válido
```

Esto puede ser intencional (no tendría sentido "dar de cambio" el monto total que se recibió — sería regresar todo el dinero), pero **conviene señalarlo como un posible off-by-one** si el objetivo real era listar _todos_ los montos posibles.

---

#### 💻 Por qué esto es "mochila 0/1" y no "cambio de monedas clásico"

```
Cambio de monedas clásico (monedas ILIMITADAS):
  matriz[i][j] = matriz[i][j - billetes[i]]  ← usa la MISMA fila i
                                                (se puede reusar billetes[i])

Este código (monedas LIMITADAS a 1 unidad):
  matriz[i][j] = matriz[i-1][j - billetes[i]] ← usa la fila ANTERIOR i-1
                                                 (billetes[i] se usa como máximo 1 vez)
```

Esa única diferencia de índice (`i` vs `i-1`) es la que distingue "monedas infinitas" de "una sola moneda de cada tipo", y coincide exactamente con el enunciado: la tienda tiene un conjunto **limitado**.

---

#### ⏱️ Complejidad

```
Filas:     tamanio  (número de denominaciones, incluyendo el "0" ficticio)
Columnas:  suma + 1 (suma total de todas las monedas)

Tiempo:   O(tamanio × suma)
Espacio:  O(tamanio × suma)   (matriz completa; podría reducirse a O(suma) 
                                usando solo la fila anterior)
```

Para el ejemplo (`tamanio=4`, `suma=17`) son apenas 68 celdas — instantáneo.

---

#### 🎯 Resumen

|Elemento|Explicación|
|---|---|
|**Problema**|¿Qué montos de cambio se pueden dar con un conjunto limitado de monedas?|
|**Tipo de DP**|Subset-sum / Mochila 0/1 booleana|
|**Estado**|`matriz[i][j]` = ¿es posible formar la suma `j` usando billetes[0..i]?|
|**"Moneda" ficticia**|`billetes[0]=0` solo sirve como caso base de la fila 0|
|**Recurrencia**|`max(no usar la moneda, usarla y restar su valor)`|
|**Diferencia vs. cambio clásico**|Usa `matriz[i-1][...]` en vez de `matriz[i][...]` → cada moneda se usa a lo sumo una vez|
|**Resultado para {2,5,10}**|Montos alcanzables: 0, 2, 5, 7, 10, 12, 15, (17 técnicamente también, pero no se imprime por el `i < suma`)|
|**Complejidad**|O(tamanio × suma) tiempo y espacio|