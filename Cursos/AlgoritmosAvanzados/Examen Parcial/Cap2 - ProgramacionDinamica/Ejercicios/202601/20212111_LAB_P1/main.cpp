#include <iostream>
using namespace std;

int main() {
    int inicio[] = {1, 4, 6, 6, 5, 8};
    int fin[] = {3, 5, 8, 8, 9, 12};
    int pago[] = {30, 10, 60, 20, 50, 40};
    int n = 6;

    int dp[n + 1];
    int evento_compatible[n + 1];
    int bono_aplicado[n + 1];

    dp[0] = 0;
    evento_compatible[0] = -1;
    bono_aplicado[0] = 0;

    for (int i = 1; i <= n; i++) {
        // Op1: No seleccionar evento i
        dp[i] = dp[i - 1];
        evento_compatible[i] = -1;
        // Op2: Seleccionar evento i-1
        int evento_actual = i - 1;
        // Buscar el ultimo evento j compatible
        int j = -1;
        for (int k = i - 2; k >= 0; k--) {
            if (fin[k] + 1 <= inicio[evento_actual]) {
                j = k;
                break;
            }
        }
        // Calcular ganacia si seleccionamos evento i-1
        int bono = 0;
        int ganancia;
        if (j >= 0) {
            if (fin[j] + 1 == inicio[evento_actual]) {
                bono = 15;
            }
            ganancia = pago[evento_actual] + bono + dp[j + 1];
        } else {
            // No hay evento anterior compatible
            ganancia = pago[evento_actual];
        }
        // Actualizar DP
        if (ganancia > dp[i]) {
            dp[i] = ganancia;
            evento_compatible[i] = j;
            bono_aplicado[i] = bono;
        }
    }
    for (int i=1;i<=n;i++) {
        cout << dp[i] << " ";
    }
    cout << "Ganancia maxima es: "<< dp[n]<< endl;

    return 0;
}
