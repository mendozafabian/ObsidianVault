#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Tobejto {
    int id;
    int cant;
};

struct Tresultado {
    int idCamion;
    int idPaquete;
};

bool lt(Tobejto a, Tobejto b) {
    return a.cant < b.cant;
}

bool gt(Tobejto a, Tobejto b) {
    return a.cant > b.cant;
}

void mostrar(vector<Tobejto> o) {
    for (int i = 0; i < o.size(); i++) {
        cout << "Id: " << o[i].id << " ";
        cout << "Cant: " << o[i].cant << endl;
    }
    cout << endl;
}

void cargarCamion(vector<Tobejto> paquetes, vector<Tobejto> camiones) {
    vector<Tresultado> resultados;
    sort(paquetes.begin(), paquetes.end(), gt);
    sort(camiones.begin(), camiones.end(), lt);
    cout << "Camiones ordenados en forma ascendente: " << endl;
    mostrar(camiones);
    cout << "Paquetes ordenados en forma descendente: " << endl;
    mostrar(paquetes);
    for (int i = 0; i < paquetes.size(); i++) {
        for (int j = 0; j < camiones.size(); j++) {
            if (camiones[j].cant >= paquetes[i].cant) {
                camiones[j].cant -= paquetes[i].cant;
                resultados.push_back({camiones[j].id, paquetes[i].id});
                break;
            }
        }
    }
    cout << "Resultado:" << endl;
    for (int i = 0; i < resultados.size(); i++) {
        cout << "Id camion: " << resultados[i].idCamion << " ";
        cout << "Id paquete: " << resultados[i].idPaquete << endl;
    }
}

int main() {
    vector<Tobejto> paquetes = {
        {1, 150},
        {2, 100},
        {3, 180},
        {4, 100},
        {5, 300}
    };
    vector<Tobejto> camiones = {
        {1, 250},
        {2, 200},
        {3, 200},
        {4, 100},
        {5, 300}
    };
    cargarCamion(paquetes, camiones);
    return 0;
}
