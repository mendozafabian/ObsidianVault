#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define MAX 8

struct Nodo {
    int punto;
    int distancia;
};

bool lt(Nodo a, Nodo b) {
    return a.distancia < b.distancia;
}

bool gt(Nodo a, Nodo b) {
    return a.distancia > b.distancia;
}

void crearRutaMinima(int inicio, int fin, int mapa[][MAX]) {
    cout << "Ciudad inicial: " << inicio << endl;
    cout << "Ciudad final: " << fin << endl;
    int distanciaRecorrida = 0;
    int ciudad = inicio;
    cout << "Recorrido: " << ciudad;
    while (true) {
        vector<Nodo> vecinos;
        for (int i = 0; i < MAX; i++) {
            if (mapa[ciudad][i]>0) {
                Nodo aux;
                aux.punto = i;
                aux.distancia = mapa[ciudad][i];
                vecinos.push_back(aux);
            }
        }
        if (not vecinos.empty()) {
            sort(vecinos.begin(), vecinos.end(), lt);
            ciudad = vecinos[0].punto;
            cout << " -> " << ciudad;
            distanciaRecorrida += vecinos[0].distancia;
        }
        if (ciudad == fin) {
            cout << endl << "Hay solucion." << endl;
            break;
        }
        if (vecinos.empty()) {
            cout << endl << "No hay solucion." << endl;
            break;
        }
    }
}

int main() {
    int mapa[][MAX]{
        {0, 4, 5, 6, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0, 0, 10, 0},
        {0, 0, 0, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    crearRutaMinima(0, 7, mapa);
    return 0;
}
