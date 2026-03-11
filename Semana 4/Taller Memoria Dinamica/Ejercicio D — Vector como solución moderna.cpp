#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;

    cout << "Ingrese tamaño: ";
    cin >> n;

    vector<int> arr(n);
    int suma = 0;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        suma += arr[i];
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    cout << "\nPromedio: " << (double)suma / n;

    return 0;
}