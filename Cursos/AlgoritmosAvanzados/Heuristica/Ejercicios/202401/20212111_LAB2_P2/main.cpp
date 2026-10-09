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

void llenarContenedor(vector<Paquete> paquetes, int pesoMaximo) {
    sort(paquetes.begin(), paquetes.end(), gt);
    int residuo = pesoMaximo;
    int gananciaAcumulada = 0;
    for (int i = 0; i < paquetes.size(); i++) {
        if (residuo >= paquetes[i].peso) {
            residuo -= paquetes[i].peso;
            gananciaAcumulada += paquetes[i].ganancia;
        }
    }
    cout << "Peso sobrante en el contenedor: " << residuo << " Tn."<< endl;
    cout << "Ganancia de la exportacion: "<< gananciaAcumulada << " en miles de dolares."<< endl;
}

int main() {
    vector<Paquete> paquetes = {
        {10, 2},
        {15, 3},
        {10, 5},
        {24, 12},
        {8, 2}
    };
    int pesoMaximo = 16;
    llenarContenedor(paquetes, pesoMaximo);
    Paquete paquete;
    paquete.ganancia = 5;
    paquete.peso = 5;
    paquetes.push_back(paquete);
    pesoMaximo = 20;
    llenarContenedor(paquetes, pesoMaximo);
    return 0;
}
