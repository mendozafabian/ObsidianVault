# Guía Completa: Estrategia Algorítmica de Backtracking

Esta guía está diseñada para comprender a fondo la técnica de **Backtracking** (o "vuelta atrás"), abordando desde sus fundamentos teóricos hasta su aplicación práctica en problemas clásicos de la ciencia de la computación.

*Basado en el documento de referencia: "1INF32 - 01 - Estrategias - Backtracking.pdf".*

---

## 1. Introducción y Definición

El **Backtracking** es una estrategia algorítmica utilizada para encontrar soluciones a problemas mediante el método de **ensayo y error**. 

La viabilidad de esta resolución se basa en descomponer el problema principal en varias tareas parciales intermedias. Generalmente, estas tareas parciales se realizan de manera recursiva, explorando un espacio de posibles respuestas.

### ¿Cómo funciona?
1. El proceso se basa en ir tomando decisiones (se evalúan exhaustivamente todas las posibles).
2. Una vez tomada una decisión, se evalúa la viabilidad del resto de la solución.
3. Si la decisión conduce a la solución final, el algoritmo se detiene y termina (o guarda la solución si se buscan todas).
4. **La clave:** Si la decisión *no* conduce a la solución final, se deshace la decisión tomada (esto es el *"backtrack"* o "marcha atrás") y se toma otra opción disponible.

---

## 2. Características Principales

*   Itera a través de todas las combinaciones posibles en el espacio de búsqueda.
*   Puede ser adaptada para cada aplicación particular o problema específico.
*   Siempre puede encontrar todas las soluciones existentes (si se configura para no detenerse en la primera).
*   **Desventaja principal:** El tiempo que toma para encontrar las soluciones, ya que en el peor de los casos evalúa todas las combinaciones (complejidad exponencial).

### Ventajas y Desventajas

| Ventajas | Desventajas |
| :--- | :--- |
| Se aplica especialmente en problemas combinatorios difíciles para los cuales no hay algoritmos eficientes (exactos). | Puede estancarse y demorarse mucho tiempo para darse cuenta de que una configuración no tiene solución. |
| A diferencia de la búsqueda exhaustiva pura (fuerza bruta), alberga la esperanza de resolver el problema en un tiempo aceptable al podar caminos inválidos. | Puede consumir muchos recursos del computador (especialmente memoria de pila por la recursividad profunda). |
| No elimina ningún elemento del espacio de estados, lo que permite revisar todas las combinaciones si es necesario. | |

---

## 3. Versión General del Algoritmo (Plantilla)

La estructura clásica de un algoritmo de backtracking se puede modelar con el siguiente pseudocódigo:

```text
Procedimiento Backtrack (nivel)
    Si nivel es una solución válida entonces
        Imprimir solución
    Sino
        Para cada opción posible en este nivel hacer
            Si la opción es factible entonces
                Hacer elección (modificar estado)
                Backtrack(nivel + 1)
                Deshacer elección (rollback de la modificación)
Fin Procedimiento
```

### Explicación del flujo:
1. Se define un procedimiento recursivo que recibe el `nivel` (profundidad actual).
2. Se verifica si el `nivel` representa una solución completa.
3. Si no es solución, iteramos sobre las opciones:
   - Verificamos si la opción es válida (restricciones).
   - Aplicamos la opción.
   - Llamamos recursivamente para avanzar.
   - **Revertimos la opción** para explorar otras ramas.

---

## 4. Ejercicios Resueltos

A continuación, analizaremos dos de las aplicaciones más famosas del Backtracking, mencionadas en el material del curso.

### Ejercicio 1: El Problema de las N-Reinas

**Problema:** En un tablero de ajedrez de $N \times N$ posiciones, colocar $N$ reinas de tal manera que no se puedan atacar entre sí (no compartan la misma fila, columna ni diagonales).

**Proceso de Backtracking:**
1. Empezar en la columna más a la izquierda.
2. Si todas las reinas han sido ubicadas, la solución está completa.
3. Para cada fila de la columna actual:
   - Si la reina se puede colocar de forma segura, se coloca.
   - Se intenta colocar el resto de las reinas en las siguientes columnas de forma recursiva.
   - Si la recursión falla, se quita la reina (backtrack) y se prueba la siguiente fila.

**Implementación Práctica (Python):**

```python
def resolver_n_reinas(N):
    tablero = [[0 for _ in range(N)] for _ in range(N)]
    
    def es_seguro(tablero, fila, col):
        # Revisar fila hacia la izquierda
        for i in range(col):
            if tablero[fila][i] == 1: return False
        # Revisar diagonal superior izquierda
        for i, j in zip(range(fila, -1, -1), range(col, -1, -1)):
            if tablero[i][j] == 1: return False
        # Revisar diagonal inferior izquierda
        for i, j in zip(range(fila, N, 1), range(col, -1, -1)):
            if tablero[i][j] == 1: return False
        return True

    def backtrack(col):
        # Caso base: Si todas las reinas están colocadas
        if col >= N: return True
        
        for fila in range(N):
            if es_seguro(tablero, fila, col):
                # 1. Hacer elección
                tablero[fila][col] = 1 
                
                # 2. Explorar
                if backtrack(col + 1): 
                    return True
                    
                # 3. Deshacer elección (Backtrack)
                tablero[fila][col] = 0 
                
        return False # Desencadena el backtracking anterior

    if backtrack(0):
        for fila in tablero: print(fila)
    else:
        print("No hay solución")

resolver_n_reinas(4)
```

---

### Ejercicio 2: Sudoku

**Problema:** Dada una matriz de $9 \times 9$ parcialmente llena, asignar dígitos del 1 al 9 a las celdas vacías de tal forma que cada fila, columna y submatriz de $3 \times 3$ contenga exactamente una instancia de los dígitos del 1 al 9.

**Proceso de Backtracking:**
Buscamos una celda vacía. Si no hay, resolvimos el Sudoku. Si encontramos una, probamos los números del 1 al 9. Si el número es válido según las reglas, lo colocamos y llamamos recursivamente. Si llegamos a un punto sin salida, borramos el número y probamos el siguiente.

**Implementación Práctica (Python):**

```python
def resolver_sudoku(tablero):
    def encontrar_vacio(tablero):
        for i in range(9):
            for j in range(9):
                if tablero[i][j] == 0:
                    return i, j
        return None

    def es_valido(tablero, num, pos):
        # Revisar fila
        for j in range(9):
            if tablero[pos[0]][j] == num and pos[1] != j: return False
        # Revisar columna
        for i in range(9):
            if tablero[i][pos[1]] == num and pos[0] != i: return False
        # Revisar caja 3x3
        caja_x = pos[1] // 3
        caja_y = pos[0] // 3
        for i in range(caja_y * 3, caja_y * 3 + 3):
            for j in range(caja_x * 3, caja_x * 3 + 3):
                if tablero[i][j] == num and (i, j) != pos: return False
        return True

    def backtrack():
        vacio = encontrar_vacio(tablero)
        if not vacio:
            return True # No hay celdas vacías, ¡resuelto!
        else:
            fila, col = vacio

        for num in range(1, 10): # Opciones del 1 al 9
            if es_valido(tablero, num, (fila, col)):
                tablero[fila][col] = num # Hacer elección

                if backtrack(): # Explorar
                    return True

                tablero[fila][col] = 0 # Deshacer elección (Backtrack)

        return False

    return backtrack()
```

---

## 5. Ejercicios Propuestos para Practicar

Para dominar esta técnica, intenta aplicar la plantilla general a los siguientes problemas clásicos:

1.  **Generación de Permutaciones:** Dado un string "ABC", genera todas sus posibles combinaciones (ABC, ACB, BAC, BCA, CAB, CBA) usando Backtracking.
2.  **Laberinto (Rat in a Maze):** Dada una matriz bidimensional de unos (caminos) y ceros (paredes), encuentra un camino desde la esquina superior izquierda a la inferior derecha. Recuerda deshacer tus pasos si un camino lleva a un callejón sin salida.
3.  **Suma de Subconjuntos (Subset Sum):** Dado un arreglo de números positivos enteros y un número objetivo `X`, encuentra todas las combinaciones de números que sumen exactamente `X`.

---
*Referencia Bibliográfica de la Guía Original:* 
LEVITIN, A. Introduction to The Design and Analysis of Algorithms. 3ra edición. USA: Pearson, 2012. ISBN-13 978-0-13-231681-1