#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 8;

struct Nodo {
    int ciudad;
    int distancia;
};

bool lt(Nodo a, Nodo b) {
    return a.distancia < b.distancia;
}

bool gt(Nodo a, Nodo b) {
    return a.distancia > b.distancia;
}

void calcularRuta(int inicio, int fin, int mapa[][N]) {
    int distanciaRecorrida = 0;
    cout << "Ciudad inicial: " << inicio << endl;
    cout << "Ciudad final: " << fin << endl;
    int ciudad = inicio;
    cout << "Recorrido: " << ciudad;
    while (true) {
        vector<Nodo> vecinos;
        for (int i = 0; i < N; i++) {
            if (mapa[ciudad][i] > 0) {
                Nodo aux;
                aux.ciudad = i;
                aux.distancia = mapa[ciudad][i];
                vecinos.push_back(aux);
            }
        }
        if (not vecinos.empty()) {
            sort(vecinos.begin(), vecinos.end(), lt);
            ciudad = vecinos[0].ciudad;
            cout << " -> " << ciudad;
            distanciaRecorrida += vecinos[0].distancia;
        }
        if (ciudad == fin) {
            break;
        }
        if (vecinos.empty()) {
            cout << endl << "No hay solucion." << endl;
            break;
        }
    }
    cout << endl << "Distancia recorrida: " << distanciaRecorrida << endl;
}

int main() {
    int mapa[][N] = {
        {0, 4, 5, 6, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0, 0, 10, 0},
        {0, 0, 0, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    calcularRuta(0, 6, mapa);
    return 0;
}
