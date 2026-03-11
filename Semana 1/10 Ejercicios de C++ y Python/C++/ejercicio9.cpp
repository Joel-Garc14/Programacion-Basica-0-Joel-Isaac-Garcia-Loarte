#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Ingrese dos numeros: ";
    cin >> a >> b;

    if (a > b)
        cout << a << " es mayor que " << b;
    else if (a < b)
        cout << a << " es menor que " << b;
    else
        cout << "Los numeros son iguales";

    return 0;
}
