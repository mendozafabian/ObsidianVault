### **CompraDolaresPD** - Best Time to Buy & Sell Stock (k transacciones)

#### 📖 ¿Qué hace?

Maximiza ganancia comprando y vendiendo acciones con **hasta k transacciones permitidas** (compra y venta = 1 transacción).

#### 🔄 Lógica paso a paso

```cpp
int ganancia(int k, int n, int *precios) {
    // dp[i][j] = máxima ganancia con i transacciones hasta día j
    int dp[k+1][n];
    
    // Base: 0 transacciones = 0 ganancia
    for (int i=0; i<=k; i++) 
        dp[i][0] = 0;
    
    // Base: sin transacciones = 0 ganancia
    for (int i=1; i<n; i++)  
        dp[0][i] = 0;
    
    // Llenar la tabla
    for (int i=1; i<=k; i++) {
        for (int j=1; j<n; j++) {
            // Buscar el mejor día m para haber comprado
            int maximo = INT_MIN;
            for (int m=0; m<j; m++) {
                // Ganancia si compré en día m y vendo en día j
                maximo = max(maximo, precios[j] - precios[m] + dp[i-1][m]);
            }
            // Opción: hacer transacción o no hacerla
            dp[i][j] = max(maximo, dp[i][j-1]);
        }
    }
}
```

#### 📊 Ejemplo: `k=3`, `precios = {300, 320, 350, 330, 360, 380}`

```
Tabla dp (máxima ganancia):

Trans↓ 300  320  350  330  360  380
  0    0    0    0    0    0    0
  1    0   20   50   50   60   80
  2    0   20   50   70   90   100
  3    0   20   50   70   90   110
  
Respuesta: 110
```

**Mejor estrategia:**

- Compra a 300, vende a 350 → Ganancia: 50
- Compra a 330, vende a 380 → Ganancia: 50
- Compra a 360, vende a 360 → Ganancia: 0
- **Total: 110**