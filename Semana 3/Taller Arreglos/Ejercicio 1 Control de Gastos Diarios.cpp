#include <iostream>
using namespace std;

int main() {
    int gastos[7];
    int suma = 0;
    int mayor = 0;
    int promedio;

    for (int i = 0; i < 7; i++) {
        cin >> gastos[i];
        suma = suma + gastos[i];
    }

    promedio = suma / 7;

    for (int i = 0; i < 7; i++) {
        if (gastos[i] > promedio) {
            mayor++;
        }
    }

    cout << "Total: " << suma << endl;
    cout << "Promedio: " << promedio << endl;
    cout << "Dias con gasto mayor al promedio: " << mayor << endl;

    return 0;
}