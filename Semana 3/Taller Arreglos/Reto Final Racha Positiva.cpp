#include <iostream>
using namespace std;

int main() {
    int datos[8];
    int racha = 0, mayorRacha = 0;

    for (int i = 0; i < 8; i++) {
        cin >> datos[i];
    }

    for (int i = 0; i < 8; i++) {
        if (datos[i] > 0) {
            racha++;

            if (racha > mayorRacha) {
                mayorRacha = racha;
            }
        } 
        else {
            racha = 0;
        }
    }

    cout << "Mayor racha positiva: " << mayorRacha << " dias" << endl;

    return 0;
}