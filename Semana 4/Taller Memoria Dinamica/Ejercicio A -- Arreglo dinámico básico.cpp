#include <iostream>
using namespace std;

int main() {
    int n;
    
    // Solicitar tamaño del arreglo
    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;
    
    // Validar que el tamaño sea positivo
    if (n <= 0) {
        cout << "Error: El tamaño debe ser mayor que 0." << endl;
        return 1;
    }
    
    // Crear arreglo dinámico
    int* arr = new int[n];
    int suma = 0;
    
    // Ingresar elementos y calcular suma
    for(int i = 0; i < n; i++) {
        cout << "Ingrese número " << i + 1 << ": ";
        cin >> arr[i];
        suma += arr[i];
    }
    
    // Mostrar el arreglo
    cout << "\nArreglo ingresado: [ ";
    for(int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << " ]" << endl;
    
    // Calcular y mostrar promedio
    double promedio = (double)suma / n;
    cout << "Promedio: " << promedio << endl;
    
    // Liberar memoria
    delete[] arr;
    
    return 0;
}