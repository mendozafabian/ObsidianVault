#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Proyecto {
    int id;
    int costo;
    int ganancia;
    int beneficio;
    vector<int> predecesores;
};

bool lt(Proyecto a, Proyecto b) {
    return (double) (a.beneficio * a.ganancia) / a.costo < (double) (b.beneficio * b.ganancia) / b.costo;
}

bool gt(Proyecto a, Proyecto b) {
    return (double) (a.beneficio * a.ganancia) / a.costo > (double) (b.beneficio * b.ganancia) / b.costo;
}

bool verificar(Proyecto proyecto, vector<int> soluciones) {
    int contador = 0;
    if (proyecto.predecesores.size() == 0) return true;
    for (int i = 0; i < proyecto.predecesores.size(); i++) {
        for (int j = 0; j < soluciones.size(); j++) {
            if (proyecto.predecesores[i] == soluciones[j]) {
                contador++;
            }
        }
    }
    if (contador == proyecto.predecesores.size()) return true;
    return false;
}

void seleccionarProyectos(vector<Proyecto> proyectos, int presupuesto) {
    sort(proyectos.begin(), proyectos.end(), gt);
    cout << "Proyectos ordenados por ratio: " << endl;
    for (int i = 0; i < proyectos.size(); i++) {
        cout << "Id: " << proyectos[i].id << " - ";
        cout << "Ratio: " << (double) (proyectos[i].beneficio * proyectos[i].ganancia) / proyectos[i].costo << endl;
    }
    int i = 0, costoAcumulado = 0, gananciaAcumulada = 0, benificioAcumulado = 0;
    vector<int> soluciones;
    while (i < proyectos.size() and costoAcumulado < presupuesto and proyectos.size() > 0) {
        if (presupuesto >= costoAcumulado + proyectos[i].costo and verificar(proyectos[i], soluciones)) {
            costoAcumulado += proyectos[i].costo;
            gananciaAcumulada += proyectos[i].ganancia;
            benificioAcumulado += proyectos[i].beneficio;
            soluciones.push_back(proyectos[i].id);
            proyectos.erase(proyectos.begin() + i);
            i = 0;
        } else i++;
    }
    cout << "Solucion: " << endl;
    for (int i = 0; i < soluciones.size(); i++) {
        cout << "Id: " << soluciones[i];
        if (i < soluciones.size() - 1) cout << " -> ";
        else cout << endl;
    }
    cout << "Costo acumulado: " << costoAcumulado << endl;
    cout << "Ganancia acumulada: " << gananciaAcumulada << endl;
    cout << "Beneficio acumulado: " << benificioAcumulado << endl;
}

int main() {
    vector<Proyecto> proyectos = {
        {1, 80, 150, 2, {}},
        {2, 20, 80, 5, {4}},
        {3, 100, 300, 1, {1, 2}},
        {4, 100, 150, 4, {}},
        {5, 50, 80, 2, {}},
        {6, 10, 50, 1, {2}},
        {7, 50, 120, 2, {6}},
        {8, 50, 150, 4, {6}},
    };
    int presupuesto = 250;
    seleccionarProyectos(proyectos, presupuesto);
    return 0;
}
