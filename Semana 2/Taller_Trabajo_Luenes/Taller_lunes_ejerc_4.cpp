#include <iostream>
using namespace std;

int main() 
{
    int opcion;
    cin >> opcion;

    switch (opcion) {
       case 1:
       cout << "Suma";
            break;
        case 2:
            cout << "Resta";
            break;
        case 3:
            cout << "Multiplicacion";
            break;
        case 4:
            cout << "Division";
            break;
        default:
            cout << "Opcion no valida";
    }

    return 0;
}
