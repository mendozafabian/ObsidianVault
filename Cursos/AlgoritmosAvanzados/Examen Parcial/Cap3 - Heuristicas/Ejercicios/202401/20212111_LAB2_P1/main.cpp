#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define N 8

struct Nodo {
    int ciudad;
    int tiempo;
};

bool lt(Nodo a, Nodo b) {
    return a.tiempo < b.tiempo;
}

void encontrarRuta(int inicio, int fin, int mapa[][N]) {
    cout << "Inicio: " << inicio << endl;
    cout << "Fin: " << fin << endl;
    int ciudad = inicio;
    int tiempoTranscurrido = 0;
    bool solucion = false;
    cout << "Recorrido: " << ciudad;
    while (true) {
        vector<Nodo> vecinos;
        for (int i = 0; i < N; i++) {
            if (mapa[ciudad][i] > 0) {
                Nodo aux;
                aux.ciudad = i;
                aux.tiempo = mapa[ciudad][i];
                vecinos.push_back(aux);
            }
        }
        if (not vecinos.empty()) {
            sort(vecinos.begin(), vecinos.end(), lt);
            ciudad = vecinos[0].ciudad;
            cout << " -> " << ciudad;
            tiempoTranscurrido += vecinos[0].tiempo;
        }
        if (ciudad == fin) {
            solucion = true;
            break;
        }
        if (vecinos.empty()) {
            break;
        }
    }
    if (solucion) {
        cout << endl << "Tiempo de viaje: " << tiempoTranscurrido << " min." << endl;
    } else {
        cout << endl << "No se encontro una solucion." << endl;
    }
    cout<<endl;
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
    encontrarRuta(0, 6, mapa);
    encontrarRuta(3, 6, mapa);
    encontrarRuta(2, 6, mapa);
    return 0;
}
