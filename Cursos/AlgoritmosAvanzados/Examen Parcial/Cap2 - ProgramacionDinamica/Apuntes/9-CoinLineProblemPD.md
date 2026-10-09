#### 📋 Entendimiento del Problema

**Objetivo:** Contar todas las formas válidas de colocar en una **fila** monedas de tres denominaciones:

- `p` monedas de **1 sol**
- `q` monedas de **2 soles**
- `r` monedas de **5 soles**

🚫 **Restricción:** Dos monedas de la **misma denominación** no pueden quedar adyacentes en la fila.

**Estados de la recursión — `dp[p][q][r][last_idx]`:**

```
p, q, r      → cuántas monedas de cada tipo QUEDAN por colocar
last_idx     → denominación de la ÚLTIMA moneda ya colocada

last_idx = 0 → aún no se colocó ninguna moneda (inicio)
last_idx = 1 → la última fue de 1 sol
last_idx = 2 → la última fue de 2 soles
last_idx = 3 → la última fue de 5 soles
```

Cada llamada responde a la pregunta: _"con estas cantidades restantes, y sabiendo qué acabo de poner, ¿de cuántas formas puedo terminar la fila?"_

---

#### 🔍 Análisis de Restricciones

##### ✅ Transiciones Válidas

```
Desde last_idx = 1 (puse un sol):
  ✗ → poner otro sol            (dos "1 sol" adyacentes)
  ✓ → poner 2 soles
  ✓ → poner 5 soles

Desde last_idx = 2 (puse dos soles):
  ✓ → poner 1 sol
  ✗ → poner otro "2 soles"      (dos "2 soles" adyacentes)
  ✓ → poner 5 soles

Desde last_idx = 3 (puse cinco soles):
  ✓ → poner 1 sol
  ✓ → poner 2 soles
  ✗ → poner otro "5 soles"      (dos "5 soles" adyacentes)
```

##### 🚫 Por qué existe la restricción

```
... [1 sol] [1 sol] ...
        ↑       ↑
    ADYACENTES, misma denominación → INVÁLIDO

Por eso, en el código:
  if (p > 0 && last_idx != 1)   ← "queda esta moneda" Y "no es igual a la anterior"
```

Cada rama del `if` representa: _"¿puedo poner este tipo de moneda a continuación?"_ → sí, si quedan unidades **y** no se repite el tipo recién colocado.

---

#### 📊 Ejecución del Algoritmo para p=2, q=2, r=1

Como es memoización _top-down_, la primera llamada (`p=2,q=2,r=1,last=0`) dispara sub-llamadas hacia estados más pequeños. Para verlo con claridad, lo reconstruimos **de abajo hacia arriba** (los casos base primero), que es exactamente lo que la tabla `dp` va guardando conforme la recursión regresa.

##### 📐 Casos base (0 monedas restantes)

```
f(0,0,0,last) = 1   para cualquier last (0,1,2,3)
```

##### 🔄 Total = 1 moneda restante

cpp

```cpp
f(1,0,0,last):
  last=1 → 0   (la única moneda que queda es "1 sol", pero la anterior ya fue "1 sol")
  last≠1 → 1   (coloco el sol y termino)

f(0,1,0,last):  análogo con "2 soles"   → last=2:0, resto:1
f(0,0,1,last):  análogo con "5 soles"   → last=3:0, resto:1
```

##### 🔄 Total = 2 monedas restantes

cpp

```cpp
f(1,1,0,last):
  ways = [p>0 && last!=1] f(0,1,0,1)  +  [q>0 && last!=2] f(1,0,0,2)
       =            (1)                +            (1)

  last=0: 1+1 = 2
  last=1: 0+1 = 1   (se bloquea la rama de "1 sol")
  last=2: 1+0 = 1   (se bloquea la rama de "2 soles")
  last=3: 1+1 = 2
```

```
f(2,0,0,last) = 0  para TODO last
```

**Interpretación:** con solo monedas de 1 sol (2 de ellas) es _imposible_ evitar que queden adyacentes → 0 formas. Esto es clave: el algoritmo "descubre" solo, sin reglas especiales, que ciertas combinaciones son irrealizables.

##### 🔄 Total = 3 monedas restantes (ejemplo clave: `f(1,1,1,·)`)

cpp

```cpp
f(1,1,1,last):
  ways = [last!=1] f(0,1,1,1)  +  [last!=2] f(1,0,1,2)  +  [last!=3] f(1,1,0,3)
       =        (2)             +        (2)             +        (2)

  last=0: 2+2+2 = 6   (ninguna rama bloqueada)
  last=1: 0+2+2 = 4   (se bloquea "1 sol")
  last=2: 2+0+2 = 4   (se bloquea "2 soles")
  last=3: 2+2+0 = 4   (se bloquea "5 soles")
```

##### 🔄 Total = 4 monedas restantes

cpp

```cpp
f(2,1,1,last):
  ways = [last!=1] f(1,1,1,1)  +  [last!=2] f(2,0,1,2)  +  [last!=3] f(2,1,0,3)
       =        (4)             +        (1)             +        (1)
  last=0: 4+1+1 = 6
  last=1: 0+1+1 = 2
  last=2: 4+0+1 = 5
  last=3: 4+1+0 = 5

f(1,2,1,last):  (simétrico, intercambiando p↔q)
  last=0: 6   last=1: 5   last=2: 2   last=3: 5
```

##### 🎯 Total = 5 monedas restantes → la respuesta final

cpp

```cpp
f(2,2,1,0) = [last≠1] f(1,2,1,1)  +  [last≠2] f(2,1,1,2)  +  [last≠3] f(2,2,0,3)
           =        5              +        5              +        2
           = 12
```

---

#### 📋 Tabla resumen de estados usados

|Estado (p,q,r)|last=0|last=1|last=2|last=3|
|---|---|---|---|---|
|(0,0,0)|1|1|1|1|
|(1,0,0)|1|0|1|1|
|(0,1,0)|1|1|0|1|
|(0,0,1)|1|1|1|0|
|(1,1,0)|2|1|1|2|
|(2,0,0)|0|0|0|0|
|(1,0,1)|2|1|2|1|
|(0,1,1)|2|2|1|1|
|(1,1,1)|6|4|4|4|
|(2,1,1)|6|2|5|5|
|(1,2,1)|6|5|2|5|
|**(2,2,1)**|**12**|—|—|—|

---

#### ✅ Verificación independiente

Renombrando 1 sol = A, 2 soles = B, 5 soles = C, buscamos permutaciones de `{A,A,B,B,C}` sin AA ni BB adyacentes.

```
Total de permutaciones del multiconjunto:  5! / (2!·2!·1!) = 30

Por inclusión-exclusión:
  Arreglos con "AA" pegado (bloque): 4!/2! = 12
  Arreglos con "BB" pegado (bloque): 4!/2! = 12
  Arreglos con "AA" y "BB" pegados:  3!     = 6

  Inválidos = 12 + 12 - 6 = 18
  Válidos   = 30 - 18     = 12   ✓ coincide con el resultado del DP
```

---

#### 💻 Por qué el código funciona así

cpp

```cpp
if (p > 0 && last_idx != 1) {
    ways += count_ways(dp, p - 1, q, r, 1);
}
```

- `p > 0` → todavía hay monedas de ese tipo disponibles.
- `last_idx != 1` → la restricción de no-adyacencia.
- Se llama recursivamente con `p-1` (una moneda menos) y `last_idx = 1` (ahora la última colocada es tipo 1).
- Se **suma** porque cada tipo válido representa una rama de decisión distinta y mutuamente excluyente.

cpp

```cpp
if (dp[p][q][r][last_idx] != -1) {
    return dp[p][q][r][last_idx];
}
```

Antes de recalcular, se pregunta si ese estado exacto ya se resolvió antes (por ejemplo, `f(1,1,0,1)` puede ser alcanzado desde varios caminos distintos: primero poniendo A y luego B, o llegando por otra combinación). Guardar el resultado evita repetir ese trabajo.

---

#### ⏱️ Complejidad

```
Estados posibles: (MAX_N) × (MAX_N) × (MAX_N) × 4
Trabajo por estado: O(1) (solo 3 ramas posibles)

Complejidad total: O(MAX_N³ · 4) en tiempo y espacio
```

Para el caso concreto (p=2,q=2,r=1) el número de estados realmente visitados es muy pequeño (menos de 20), por eso el resultado se calcula instantáneamente.

---

#### 🎯 Resumen

| Elemento                    | Explicación                                                          |
| --------------------------- | -------------------------------------------------------------------- |
| **Problema**                | Contar arreglos de monedas sin dos iguales adyacentes                |
| **Estado DP**               | `dp[p][q][r][last]` = formas de terminar la fila desde ahí           |
| **Restricción**             | `last_idx` recuerda qué tipo se puso antes, para prohibir repetirlo  |
| **Recurrencia**             | Suma de las ramas válidas (tipo con monedas restantes y ≠ al último) |
| **Caso base**               | `p=q=r=0` → fila completa → 1 forma                                  |
| **Resultado (p=2,q=2,r=1)** | **12** arreglos válidos                                              |
| **Complejidad**             | O(MAX_N³ · 4) tiempo y espacio                                       |