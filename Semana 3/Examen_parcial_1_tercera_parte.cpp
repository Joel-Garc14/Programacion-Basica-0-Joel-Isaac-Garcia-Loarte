#include <iostream>
using namespace std;

int main() 
{
    int op;

    int units, code;
    float price, ingreso;

    float ingreso_neto = 0;
    int ventas = 0;
    int devol = 0;
    int invalidas = 0;

    float mayor = 0, menor = 0; //Profesor aca uso esta variable para saber si es la primera transccion valida
    int primero = 1;            //asi puedo iniciar correcto el mayor y menor ingreso

    float suma_ventas = 0; //Profe esta variable me sirve para calcular el promedio de ventas validas

    int cerrado = 0; //aca cuando esta variable vale 1 significa que el dia ya fue cerrado y no se permiten mas transacciones


    long long resultado = 0;
    int cant_validas = 0; // Posorrrr como no se permiten arreglos, ni strings
    // guardo las clasificaciones A B C D como numeros 1 2 3 4 en una sola variable
    // para que este todo ordenado las transacciones validas

    do 
    {
        cout << "\n=== MI MENU DEL SISTEMA ===\n";
        cout << "1) Registrar transaccion\n";
        cout << "2) Reporte de ventas del dia\n";
        cout << "3) Reporte de transacciones\n";
        cout << "4) Cerrar dia\n";
        cout << "5) Salir\n";
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) 
        {

            if (cerrado == 1) 
            {
                cout << "No se pueden registrar transacciones. El dia esta cerrado.\n";
                // Posorr verifico primero si el dia ya fue cerrado
            // para bloquear el registro como pide el enunciado
            } 
            else 
            {
                cin >> units >> price >> code;

                if (units != 0 && price > 0) 
                {
                    // Profe esta es la condicion de transaccion valida
                    // units no debe ser cero y el precio debe ser mayor a cero

                    ingreso = units * price;
                    ingreso_neto += ingreso; //Posor aca en estos dos acumulo el ingreso neto del dia


                    if (primero == 1) 
                    {
                        mayor = ingreso;
                        menor = ingreso;  // Profe aca inicializo mayor y menor con la primera transaccion valida
                        primero = 0;
                    } 
                    else 
                    {
                        if (ingreso > mayor) mayor = ingreso;
                        if (ingreso < menor) menor = ingreso;
                    }

                    if (units > 0) 
                    {
                        ventas++;
                        suma_ventas += ingreso;
                    } 
                    else 
                    {
                        devol++;
                    }

                    int num = code;
                    if (num < 0) num = -num;

                    int suma = 0;
                    int dig = 0;

                    if (num == 0) dig = 1;

                    while (num > 0) 
                    {
                        suma += num % 10;
                        num /= 10;
                        dig++;
                    }

                    int letra;
                    if (suma % 2 == 0 && suma % 4 == 0)
                        letra = 1;   // A
                    else if (suma % 2 == 1 && suma % 6 == 0)
                        letra = 2;   // B
                    else if (dig == 3)
                        letra = 3;   // C
                    else
                        letra = 4;   // D
                         // Profe aca aplico exactamente las reglas A B C D del enunciado

                    resultado = resultado * 10 + letra;
                    cant_validas++;
                    // posor guardo la clasificacion respetando el orden
                    // sin usar arreglos ni strings


                } 
                else 
                {
                    invalidas++;
                    // profe si no cumple la condicion, la transaccion es invalida
                }
            }

        } 
        else if (op == 2) 
        {
            // profe en esta opcion muestro el reporte del dia

            cout << "INGRESO_NETO=" << ingreso_neto << endl;
            cout << "VENTAS_VALIDAS=" << ventas << endl;
            cout << "DEVOLUCIONES=" << devol << endl;
            cout << "TRANS_INVALIDAS=" << invalidas << endl;

            if (primero == 0) 
            {
                cout << "MAYOR_ING=" << mayor << endl;
                cout << "MENOR_ING=" << menor << endl;
            } 
            else 
            {
                cout << "MAYOR_ING=0\nMENOR_ING=0\n";
            }

            if (ventas > 0)
                cout << "PROM_VENTA=" << (suma_ventas / ventas) << endl;
            else
                cout << "PROM_VENTA=NO EXISTE\n";

        }
         else if (op == 3) 
         {

            long long temp = resultado;
            long long div = 1;

            for (int i = 1; i < cant_validas; i++)
                div *= 10;

            while (div > 0) {
                int v = temp / div;

                if (v == 1) cout << "A\n";
                else if (v == 2) cout << "B\n";
                else if (v == 3) cout << "C\n";
                else cout << "D\n";

                temp %= div;
                div /= 10;
                // profe voy mostrando cada letra segun fue registrada
            }

        }
         else if (op == 4)
        {
            cerrado = 1;
            cout << "Dia cerrado correctamente.\n";
            // prosor con esta opcion cierro el dia
            // pero los reportes siguen funcionando

        }

    } while (op != 5);

     // profe aca es obvio el programa termina solo cuando el usuario elige salir

    return 0;
}
