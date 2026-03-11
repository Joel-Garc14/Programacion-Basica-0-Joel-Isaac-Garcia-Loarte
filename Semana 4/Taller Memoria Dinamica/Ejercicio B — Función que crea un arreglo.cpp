#include <iostream>
using namespace std;

int* crearArreglo(int n) {
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 2;
    }

    return arr;
}

int main() {
    int n;

    cout << "Ingrese tamaño: ";
    cin >> n;

    int* arreglo = crearArreglo(n);

    for (int i = 0; i < n; i++) {
        cout << arreglo[i] << " ";
    }

    delete[] arreglo;

    return 0;
}