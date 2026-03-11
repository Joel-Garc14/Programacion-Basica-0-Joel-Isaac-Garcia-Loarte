#include <iostream>
#include <vector>

using namespace std;

int main() {
    int f, c;

    cout << "Filas: ";
    cin >> f;

    cout << "Columnas: ";
    cin >> c;

    vector<vector<int>> matriz(f, vector<int>(c));

    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cin >> matriz[i][j];
        }
    }

    for (int i = 0; i < f; i++) {
        int suma = 0;

        for (int j = 0; j < c; j++) {
            cout << matriz[i][j] << "\t";
            suma += matriz[i][j];
        }

        cout << " | Suma fila: " << suma;
        cout << endl;
    }

    return 0;
}