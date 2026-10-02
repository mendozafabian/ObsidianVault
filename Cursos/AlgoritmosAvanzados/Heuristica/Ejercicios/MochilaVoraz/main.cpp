#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool gt(int a, int b) {
    // Descendente
    return a > b;
}

bool lt(int a, int b) {
    // Ascendente
    return a < b;
}

void mostrarMochila(vector<int> paquetes) {
    int n = paquetes.size();
    for (int i = 0; i < n; i++) {
        cout << paquetes[i] << " ";
    }
    cout << endl;
}

void cargarMochila(int residuo, vector<int> paquetes) {
    sort(paquetes.begin(), paquetes.end(), gt);
    cout << "Mochila ordenada: "<<endl;
    mostrarMochila(paquetes);
    int numPaquetesIngresados = 0;
    cout << "Paquetes ingresados a la mochila: "<< endl;
    for (int i = 0; i < paquetes.size(); i++) {
        if (residuo - paquetes[i] >= 0) {
            cout <<"Paquete: "<< paquetes[i] << endl;
            residuo -= paquetes[i];
            numPaquetesIngresados++;
        }
    }
    cout << "Numero de paquetes ingresados en la mochila: " << numPaquetesIngresados << endl;
    cout << "Residuo de la mochila: " << residuo << endl;
}

int main() {
    int peso = 19;
    vector<int> paquetes = {2, 1, 2, 4, 12};
    cargarMochila(peso, paquetes);
    return 0;
}
