#include <iomanip>
#include <iostream>
using namespace std;

void imprimir(int *matriz[], int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cout << setw(3) << matriz[i][j];
        }
        cout << endl;
    }
}

void calcular(int *billetes, int tamanio) {
    int suma = 0;
    for (int i = 0; i < tamanio; i++) {
        suma += billetes[i];
    }
    int matriz[tamanio][suma + 1];
    for (int i = 0; i <= suma; i++) {
        matriz[0][i] = 0;
    }
    for (int i = 0; i < tamanio; i++) {
        matriz[i][0] = 1;
    }
    for (int i = 1; i < tamanio; i++) {
        for (int j = 1; j <= suma; j++) {
            if (billetes[i] <= j) {
                matriz[i][j] = max(matriz[i - 1][j], matriz[i - 1][j - billetes[i]]);
            } else {
                matriz[i][j] = matriz[i - 1][j];
            }
        }
    }
    for (int i = 0; i < tamanio; i++) {
        for (int j = 0; j < suma + 1; j++) {
            cout << setw(5) << matriz[i][j];
        }
        cout << endl;
    }
    cout << "Se puede dar cambio para: ";
    for (int i = 1; i <= suma; i++) {
        if (matriz[tamanio - 1][i] == 1) {
            cout << setw(5) << i;
        }
    }
}

int main() {
    int billetes[]{0, 2, 5, 10};
    int tamanio = sizeof(billetes) / sizeof(billetes[0]);
    calcular(billetes, tamanio);
    return 0;
}
