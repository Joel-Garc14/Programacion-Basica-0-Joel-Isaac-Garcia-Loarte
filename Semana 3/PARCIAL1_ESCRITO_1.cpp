#include <iostream>
using namespace std;

bool esPrimo(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool masImparesQuePares(int n) {
    int pares = 0, impares = 0;
    if (n == 0) pares++;
    else {
        int temp = (n < 0) ? -n : n;
        while (temp > 0) {
            int digito = temp % 10;
            if (digito % 2 == 0) pares++;
            else impares++;
            temp /= 10;
        }
    }
    return impares > pares;
}

int main() {
    int N;

    do{
    cout << "Ingrese la cantidad de numeros (N >= 1): ";
    cin >> N;
    } while (N<1);

    if (N < 1) return 0;

    int maximo, minimo;
    int contadorPrimos = 0;
    
    float sumaPosPares = 0;
    int contPosPares = 0;
    
    int mayorMasImpares;
    bool existeMayorMasImpares = false;

    for (int i = 0; i < N; i++) {
        int num;
        cout << "Ingrese numero " << i + 1 << ": ";
        cin >> num;

        if (i == 0) {
            maximo = minimo = num;
        } else {
            if (num > maximo) maximo = num;
            if (num < minimo) minimo = num;
        }

        if (esPrimo(num)) {
            contadorPrimos++;
        }

        if (num > 0 && num % 2 == 0) {
            sumaPosPares += num;
            contPosPares++;
        }

        if (masImparesQuePares(num)) {
            if (!existeMayorMasImpares || num > mayorMasImpares) {
                mayorMasImpares = num;
                existeMayorMasImpares = true;
            }
        }
    }

    cout << "\n------------------------------" << endl;
    cout << "1. Maximo: " << maximo << " | Minimo: " << minimo << endl;

    cout << "2. Cantidad de primos: ";
    if (contadorPrimos > 0) cout << contadorPrimos << endl;
    else cout << "NO EXISTE" << endl;

    cout << "3. Promedio positivos pares: ";
    if (contPosPares > 0) cout << (sumaPosPares / contPosPares) << endl;
    else cout << "NO EXISTE" << endl;

    cout << "4. Mayor con mas digitos impares: ";
    if (existeMayorMasImpares) cout << mayorMasImpares << endl;
    else cout << "NO EXISTE" << endl;

    return 0;
}