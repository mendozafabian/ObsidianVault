#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define MAX 6

struct Nodo {
    int ciudad;
    int distancia;
    bool conGrifo;
};

bool gt(Nodo a, Nodo b) {
    return a.distancia > b.distancia;
}

void crearRuta(int inicio, int fin, int matriz[][MAX], int capacidadInicial, vector<int> conGrifo) {
    cout << "Ciudad inicial: " << inicio << endl;
    cout << "Ciudad final: " << fin << endl;
    int ciudad = inicio;
    int capacidad = capacidadInicial;
    cout << "Recorrido: " << ciudad;
    vector<int> visitados;
    visitados.push_back(ciudad);
    while (true) {
        vector<Nodo> vecinos;
        for (int i = 0; i < MAX; i++) {
            if (matriz[ciudad][i] > 0) {
                Nodo aux;
                aux.ciudad = i;
                aux.distancia = matriz[ciudad][i];
                aux.conGrifo = (find(conGrifo.begin(), conGrifo.end(), aux.ciudad) != conGrifo.end());
                if (not (find(visitados.begin(), visitados.end(), aux.ciudad) != visitados.end())) {
                    vecinos.push_back(aux);
                }
            }
        }
        bool avanza = false;
        sort(vecinos.begin(), vecinos.end(), gt);
        if (capacidad >= vecinos[0].distancia and
            not(find(visitados.begin(), visitados.end(), vecinos[0].ciudad) != visitados.end())) {
            ciudad = vecinos[0].ciudad;
            cout << " -> " << ciudad;
            capacidad -= vecinos[0].distancia;
            if (vecinos[0].conGrifo) {
                capacidad = capacidadInicial;
            }
            visitados.push_back(ciudad);
            avanza = true;
        }
        if (ciudad == fin) {
            cout << endl << "Llega al destino." << endl;
            break;
        }
        if (not avanza) {
            cout << endl << "No se puede llegar al destino." << endl;
            break;
        }
    }
}

int main() {
    int matriz[][MAX] = {
        {0, 4, 8, 5, 0, 0},
        {4, 0, 3, 2, 6, 0},
        {8, 3, 0, 4, 7, 0},
        {5, 2, 4, 0, 3, 4},
        {0, 6, 7, 3, 0, 9},
        {0, 0, 0, 4, 9, 0}
    };
    int capacidadInicial = 10;
    vector<int> conGrifo = {0, 2};
    crearRuta(0, 5, matriz, capacidadInicial, conGrifo);
    return 0;
}
