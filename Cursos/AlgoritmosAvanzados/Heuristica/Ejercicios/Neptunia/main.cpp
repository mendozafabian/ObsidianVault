#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Paquete {
    int ganancia;
    int peso;
};

bool gt(Paquete a, Paquete b) {
    return (double) a.ganancia / a.peso > (double) b.ganancia / b.peso;
}

void cargarContenedor(vector<Paquete> paquetes, int peso) {
    sort(paquetes.begin(), paquetes.end(), gt);
    int ganancia = 0;
    int residuo = peso;
    cout << "Paquetes ingresado al contenedor: " << endl;
    for (int i = 0; i < paquetes.size(); i++) {
        if (residuo - paquetes[i].peso >= 0) {
            cout << "Paquete " << i + 1 << ": ";
            cout << "Peso: " << paquetes[i].peso << " - ";
            cout << "Ganancia: " << paquetes[i].ganancia << endl;
            residuo -= paquetes[i].peso;
            ganancia += paquetes[i].ganancia;
        }
    }
    cout << "Residuo en el contenedor: " << residuo << endl;
    cout << "Ganancia obtenida: " << ganancia << endl;
}

int main() {
    vector<Paquete> paquetes = {
        {10, 2},
        {15, 3},
        {10, 5},
        {24, 12},
        {8, 2}
    };
    int peso = 16;
    cargarContenedor(paquetes, peso);
    return 0;
}
