    #include <iostream>
    using namespace std;

    int obtenerSumaDigitos(int n) {
        int suma = 0;
        int temp = (n < 0) ? -n : n;
        
        while (temp > 0) {
            suma += (temp % 10);
            temp /= 10;
        }
        return suma;
    }

    int contarDigitos(int n) {
        int contador = 0;
        int temp = (n < 0) ? -n : n;
        
        if (temp == 0) return 1;
        
        while (temp > 0) {
            temp /= 10;
            contador++;
        }
        return contador;
    }

    int main() {
        int M;

        do {
        cout << "Ingrese la cantidad de consultas (M >= 1): ";
        cin >> M;
        } while (M<1);

        for (int i = 0; i < M; i++) {
            int x;
            cout << "Consulta " << i + 1 << ": ";
            cin >> x;

            int sumaD = obtenerSumaDigitos(x);
            int cantD = contarDigitos(x);

            if (sumaD % 2 == 0 && x % 4 == 0) {
                cout << "Resultado: A" << endl;
            }
            else if (sumaD % 2 != 0 && x % 6 == 0) {
                cout << "Resultado: B" << endl;
            }
            else if (cantD == 3) {
                cout << "Resultado: C" << endl;
            }
            else {
                cout << "Resultado: D" << endl;
            }
        }

        return 0;
    }