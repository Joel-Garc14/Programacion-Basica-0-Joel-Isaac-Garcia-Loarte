#include <iostream>
#include <string>
using namespace std;

struct Producto {
    int codigo;
    string nombre;
    float precio;
    int stock;
};

int main() {

    Producto productos[5];
    int n = 5;
    int op;

    do {
        cout << "\nMENU" << endl;
        cout << "1. Registrar productos" << endl;
        cout << "2. Mostrar productos" << endl;
        cout << "3. Buscar producto por codigo" << endl;
        cout << "4. Buscar producto por nombre" << endl;
        cout << "5. Mostrar producto con mayor stock" << endl;
        cout << "6. Mostrar producto mas caro" << endl;
        cout << "7. Calcular valor total del inventario" << endl;
        cout << "8. Salir" << endl;
        cout << "Opcion: ";
        cin >> op;

        switch(op) {

        case 1:
            for(int i = 0; i < n; i++) {
                cout << "\nProducto " << i + 1 << endl;

                cout << "Codigo: ";
                cin >> productos[i].codigo;

                cout << "Nombre: ";
                cin >> productos[i].nombre;

                do {
                    cout << "Precio: ";
                    cin >> productos[i].precio;
                } while(productos[i].precio <= 0);

                do {
                    cout << "Stock: ";
                    cin >> productos[i].stock;
                } while(productos[i].stock < 0);
            }
            break;

        case 2:
            for(int i = 0; i < n; i++) {
                cout << "\nCodigo: " << productos[i].codigo << endl;
                cout << "Nombre: " << productos[i].nombre << endl;
                cout << "Precio: " << productos[i].precio << endl;
                cout << "Stock: " << productos[i].stock << endl;
            }
            break;

        case 3: {
            int cod;
            bool encontrado = false;

            cout << "Ingrese codigo: ";
            cin >> cod;

            for(int i = 0; i < n; i++) {
                if(productos[i].codigo == cod) {
                    cout << "\nCodigo: " << productos[i].codigo << endl;
                    cout << "Nombre: " << productos[i].nombre << endl;
                    cout << "Precio: " << productos[i].precio << endl;
                    cout << "Stock: " << productos[i].stock << endl;
                    encontrado = true;
                }
            }

            if(!encontrado)
                cout << "No encontrado" << endl;

            break;
        }

        case 4: {
            string nom;
            bool encontrado = false;

            cout << "Ingrese nombre: ";
            cin >> nom;

            for(int i = 0; i < n; i++) {
                if(productos[i].nombre == nom) {
                    cout << "\nCodigo: " << productos[i].codigo << endl;
                    cout << "Nombre: " << productos[i].nombre << endl;
                    cout << "Precio: " << productos[i].precio << endl;
                    cout << "Stock: " << productos[i].stock << endl;
                    encontrado = true;
                }
            }

            if(!encontrado)
                cout << "No encontrado" << endl;

            break;
        }

        case 5: {
            int pos = 0;
            for(int i = 1; i < n; i++) {
                if(productos[i].stock > productos[pos].stock) {
                    pos = i;
                }
            }

            cout << "\nProducto con mayor stock:" << endl;
            cout << "Nombre: " << productos[pos].nombre << endl;
            cout << "Stock: " << productos[pos].stock << endl;
            break;
        }

        case 6: {
            int pos = 0;
            for(int i = 1; i < n; i++) {
                if(productos[i].precio > productos[pos].precio) {
                    pos = i;
                }
            }

            cout << "\nProducto mas caro:" << endl;
            cout << "Nombre: " << productos[pos].nombre << endl;
            cout << "Precio: " << productos[pos].precio << endl;
            break;
        }

        case 7: {
            float total = 0;
            for(int i = 0; i < n; i++) {
                total += productos[i].precio * productos[i].stock;
            }
            cout << "Valor total del inventario: " << total << endl;
            break;
        }

        case 8:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opcion invalida" << endl;
        }

    } while(op != 8);

    return 0;
}