#include <iomanip>
#include <iostream>
using namespace std;

void calcular(int *billetes, int tamanio, int meta) {
    int matriz[tamanio][meta + 1];
    for (int i = 0; i <= meta; i++) {
        matriz[0][i] = 99;
    }
    for (int i = 0; i < tamanio; i++) {
        matriz[i][0] = 0;
    }
    for (int i = 1; i < tamanio; i++) {
        for (int j = 1; j <= meta; j++) {
            if (billetes[i] <= j) {
                matriz[i][j] = min(matriz[i - 1][j], matriz[i][j - billetes[i]] + 1);
            } else {
                matriz[i][j] = matriz[i - 1][j];
            }
        }
    }
    for (int i = 0; i < tamanio; i++) {
        for (int j = 0; j <= meta; j++) {
            cout << setw(5) << matriz[i][j];
        }
        cout << endl;
    }
    cout << "Cantidad minima de billetes: " << matriz[tamanio - 1][meta] << endl;
}

int main() {
    int billetes[]{0, 2, 5, 10};
    int meta;
    cout << "Ingrese un billete para cambiar: " << endl;
    cin >> meta;
    int tamanio = sizeof(billetes) / sizeof(billetes[0]);
    if (meta == 1 or meta == 3) {
        cout << "No es posible un cambio." << endl;
    } else {
        calcular(billetes, tamanio, meta);
    }
    return 0;
}