#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool lt(int a, int b) {
    // Ascendente
    return a < b;
}

bool gt(int a, int b) {
    // Descendente
    return a > b;
}

void minCambioMonedaVoraz(vector<int> denominaciones, int cambioRestante) {
    sort(denominaciones.begin(), denominaciones.end(), gt);
    cout << "Cambio para: " << cambioRestante << endl;
    int i = 0;
    int numMonedas = 0;
    while (i < denominaciones.size() and cambioRestante > 0) {
        if (cambioRestante >= denominaciones[i]) {
            cout << "Moneda: " << denominaciones[i] << endl;
            cambioRestante -= denominaciones[i];
            numMonedas++;
        } else {
            i++;
        }
    }
    cout << "Numero de monedas en el cambio: " << numMonedas << endl;
    cout << "Cambio restante: " << cambioRestante << endl;
}

int main() {
    vector<int> denominaciones = {1, 2, 5, 10, 20, 50};
    int monto = 19;
    minCambioMonedaVoraz(denominaciones, monto);
    return 0;
}
