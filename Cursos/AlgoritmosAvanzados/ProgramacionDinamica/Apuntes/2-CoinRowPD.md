### **CoinRowPD** - Fila de Monedas (Maximizar ganancia)

#### 📖 ¿Qué hace?

Dada una fila de monedas, selecciona monedas **no adyacentes** para maximizar la cantidad de dinero. Si tomas una moneda, no puedes tomar la siguiente.

#### 🔄 Lógica paso a paso

```cpp
int calculacoin(int *mon, int n) {
    int F[n+1];  // Array DP donde F[i] = máxima ganancia hasta posición i 
    F[0]=0;      // Base: sin monedas = 0
    F[1]=mon[0]; // Base: 1ª moneda = su valor
    
    for (int i=2; i<=n; i++) {
        // Opción 1: Tomar la moneda actual + mejor hasta i-2
        int max1 = F[i-2] + mon[i-1];
        
        // Opción 2: No tomar la moneda, quedarse con mejor hasta i-1
        int max2 = F[i-1];
        
        // Elegir la mejor opción
        F[i] = max(max1,max2)
    }
}
```

#### 📊 Ejemplo: `mon = {5, 1, 2, 10, 6, 2}`

| Paso | Monedas consideradas | Decisión                   | F[i]   |
| ---- | -------------------- | -------------------------- | ------ |
| F[0] | -                    | Base                       | **0**  |
| F[1] | {5}                  | Tomar 5                    | **5**  |
| F[2] | {5,1}                | No tomar 1 (mejor: 5)      | **5**  |
| F[3] | {5,1,2}              | Tomar 2: F[1]+2=7 > 5      | **7**  |
| F[4] | {5,1,2,10}           | Tomar 10: F[2]+10=15 > 7   | **15** |
| F[5] | {...,6}              | No tomar 6: 15 > F[3]+6=13 | **15** |
| F[6] | {...,2}              | Tomar 2: F[4]+2=17 > 15    | **17** |
**Respuesta: 17** (Se toman: 5 + 10 + 2)