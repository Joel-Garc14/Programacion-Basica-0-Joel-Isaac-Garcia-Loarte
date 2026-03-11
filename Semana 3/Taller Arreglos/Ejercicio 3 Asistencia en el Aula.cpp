#include <iostream>
using namespace std;

int main() {
    int asistencia[3][5];
    int totalAula = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> asistencia[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
        int suma = 0;

        for (int j = 0; j < 5; j++) {
            suma += asistencia[i][j];
            totalAula += asistencia[i][j];
        }

        cout << "Estudiante " << i + 1 << ": " << suma << " asistencias" << endl;

        if (suma == 5) {
            cout << "Asistencia perfecta" << endl;
        }
    }

    cout << "Total de asistencias del aula: " << totalAula << endl;

    return 0;
}