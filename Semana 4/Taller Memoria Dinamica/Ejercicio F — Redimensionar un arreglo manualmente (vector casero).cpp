#include <iostream>
using namespace std;

int main() {
    int capacidad = 2;
    int tamaño = 0;
    int* arr = new int[capacidad];
    int num;

    while (true) {
        cin >> num;

        if (num == -1)
            break;

        if (tamaño == capacidad) {
            capacidad *= 2;

            int* nuevo = new int[capacidad];

            for (int i = 0; i < tamaño; i++) {
                nuevo[i] = arr[i];
            }

            delete[] arr;
            arr = nuevo;
        }

        arr[tamaño++] = num;
    }

    cout << "Numeros guardados:\n";

    for (int i = 0; i < tamaño; i++) {
        cout << arr[i] << " ";
    }

    delete[] arr;

    return 0;
}