#include <iostream>
using namespace std;

int main()
 {
    int temperatura;
    cin >> temperatura;

    if (temperatura > 30) {
        cout << "Ventilador encendido";
    } else {
        cout << "Ventilador apagado";
    }

    return 0;
}
