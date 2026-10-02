#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int sumar(int a, int b) {
    return a + b;
}

int restar(int a, int b) {
    return a - b;
}

int lt(int a, int b) {
    // Ascendente
    return a < b;
}

int gt(int a, int b) {
    // Descendente
    return a > b;
}

void mostrar(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    int (*puntf)(int, int);
    puntf = sumar;
    cout << "4 + 4 = " << puntf(4, 4) << endl;
    puntf = restar;
    cout << "4 - 4 = " << puntf(4, 4) << endl;
    vector<int> v = {12, 10, 15, 16, 20};
    puntf = gt;
    sort(v.begin(), v.end(), puntf);
    cout << "Vector descendente: " << endl;
    mostrar(v);
    puntf = lt;
    sort(v.begin(), v.end(), puntf);
    cout << "Vector ascendente: " << endl;
    mostrar(v);
    return 0;
}
