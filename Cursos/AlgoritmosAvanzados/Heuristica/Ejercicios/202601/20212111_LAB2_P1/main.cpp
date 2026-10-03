#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Tarea {
    char tarea;
    double tiempo;
    double peso;
};

bool ltPeso(Tarea a, Tarea b) {
    return a.peso < b.peso;
}

bool gtRatio(Tarea a, Tarea b) {
    return a.peso / a.tiempo > b.peso / b.tiempo;
}

void procesarTareas(vector<Tarea> tareas) {
    sort(tareas.begin(), tareas.end(), ltPeso);
    sort(tareas.begin(), tareas.end(), gtRatio);
    double completionTime = 0;
    double costoTotalPonderado = 0;
    cout << fixed << setprecision(2);
    cout << "====================================================" << endl;
    cout << "Ordenamiento final segun regla de Smith" << endl;
    cout << "====================================================" << endl;
    for (int i = 0; i < tareas.size(); i++) {
        cout << "Tarea: " << tareas[i].tarea << endl;
        cout << "Tiempo procesamiento: " << tareas[i].tiempo << endl;
        cout << "Peso: " << tareas[i].peso << endl;
        double ratio = tareas[i].peso / tareas[i].tiempo;
        cout << "Ratio w/p: " << ratio << endl;
        completionTime += tareas[i].tiempo;
        cout << "Completion time: " << completionTime << endl;
        cout << "Costo ponderado: " << tareas[i].peso * completionTime << endl;
        costoTotalPonderado += tareas[i].peso * completionTime;
        cout << "--------------------------------------" << endl;
    }
    cout << "Costo total ponderado: " << costoTotalPonderado << endl;
}

int main() {
    vector<Tarea> tareas = {
        {'A', 4, 20},
        {'B', 2, 10},
        {'C', 5, 15},
        {'D', 3, 18}
    };
    procesarTareas(tareas);
    return 0;
}
