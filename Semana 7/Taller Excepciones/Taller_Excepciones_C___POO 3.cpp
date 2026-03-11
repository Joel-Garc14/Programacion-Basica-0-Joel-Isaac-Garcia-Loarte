#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;


class CuentaNoEncontrada : public runtime_error {
public:
    CuentaNoEncontrada() : runtime_error("Cuenta no encontrada.") {}
};

class CuentaBancaria {
private:
    int numeroCuenta;
    string titular;
    double saldo;

public:
    CuentaBancaria(int n, string t, double s = 0) {
        numeroCuenta = n;
        titular = t;
        saldo = s;
    }

    void depositar(double monto) {
        if (monto <= 0)
            throw invalid_argument("El monto no puede ser negativo o cero.");
        saldo += monto;
    }

    void retirar(double monto) {
        if (monto <= 0)
            throw invalid_argument("El monto no puede ser negativo o cero.");
        if (monto > saldo)
            throw runtime_error("Saldo insuficiente.");
        saldo -= monto;
    }

    double consultarSaldo() const {
        return saldo;
    }

    int getNumeroCuenta() const {
        return numeroCuenta;
    }

    void mostrar() const {
        cout << "Cuenta: " << numeroCuenta 
             << " | Titular: " << titular 
             << " | Saldo: " << saldo << endl;
    }
};

class Banco {
private:
    vector<CuentaBancaria> cuentas;

public:
    void agregarCuenta() {
        int num;
        string nombre;

        cout << "Numero de cuenta: ";
        cin >> num;
        cout << "Titular: ";
        cin >> nombre;

        cuentas.push_back(CuentaBancaria(num, nombre));
        cout << "Cuenta creada correctamente.\n";
    }

    CuentaBancaria& buscarCuenta(int numero) {
        for (auto &c : cuentas) {
            if (c.getNumeroCuenta() == numero)
                return c;
        }
        throw CuentaNoEncontrada();
    }

    void mostrarCuentas() {
        for (const auto &c : cuentas) {
            c.mostrar();
        }
    }
};

int main() {
    Banco banco;
    int opcion;

    while (true) {
        try {
            cout << "\n1. Crear cuenta\n2. Depositar\n3. Retirar\n4. Consultar saldo\n5. Mostrar cuentas\n6. Salir\nOpcion: ";
            cin >> opcion;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw invalid_argument("Debe ingresar un numero.");
            }

            if (opcion < 1 || opcion > 6)
                throw out_of_range("Opcion fuera de rango.");

            if (opcion == 6)
                break;

            int num;
            double monto;

            switch (opcion) {
                case 1:
                    banco.agregarCuenta();
                    break;

                case 2:
                    cout << "Numero de cuenta: ";
                    cin >> num;
                    cout << "Monto: ";
                    cin >> monto;
                    banco.buscarCuenta(num).depositar(monto);
                    cout << "Deposito exitoso.\n";
                    break;

                case 3:
                    cout << "Numero de cuenta: ";
                    cin >> num;
                    cout << "Monto: ";
                    cin >> monto;
                    banco.buscarCuenta(num).retirar(monto);
                    cout << "Retiro exitoso.\n";
                    break;

                case 4:
                    cout << "Numero de cuenta: ";
                    cin >> num;
                    cout << "Saldo: " 
                         << banco.buscarCuenta(num).consultarSaldo() 
                         << endl;
                    break;

                case 5:
                    banco.mostrarCuentas();
                    break;
            }
        }
        catch (const CuentaNoEncontrada &e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const invalid_argument &e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const out_of_range &e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const runtime_error &e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    cout << "Programa finalizado correctamente.\n";
    return 0;
}

/*- Explicación breve de qué excepciones implementó y por que

puse estas excepciones profe para que el programa no se trabe si el usuario comete errores 
y pueda mostrar mensajes claros mientras sigue funcionando

- CuentaNoEncontrada: Se usa cuando no se encuentra una cuenta en el banco
- invalid_argument: Se usa cuando se ingresa un argumento inválido
- out_of_range: Se usa cuando se ingresa un número fuera de rango
- runtime_error: Se usa cuando se produce un error en tiempo de ejecución


*/