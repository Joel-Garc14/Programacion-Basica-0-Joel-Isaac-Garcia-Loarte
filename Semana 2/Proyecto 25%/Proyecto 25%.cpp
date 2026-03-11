#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Constante para el umbral de stock bajo
const double UMBRAL_STOCK_BAJO = 5.0;

// Módulo de Validación: Función que asegura que los valores numéricos sean lógicos (≥ 0)
double leerValidarDato(string mensaje) {
    double valor;
    bool valido;
    
    do {
        cout << mensaje;
        cin >> valor;
        
        if (valor < 0) {
            cout << "Error: No se permiten cantidades negativas. Intente nuevamente." << endl;
            valido = false;
        } else {
            valido = true;
        }
    } while (!valido);
    
    return valor;
}

// Estructura para almacenar los datos de cada producto
struct Producto {
    string nombre;
    double stockInicial;
    double stockFinal;
    double consumo;
    string estado;
};

// Módulo de Cálculo y Procesamiento
void procesarInventario(Producto productos[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        // Calcular stock final
        productos[i].stockFinal = productos[i].stockInicial - productos[i].consumo;
        
        // Determinar estado del stock
        if (productos[i].stockFinal < 0) {
            productos[i].estado = "STOCK NEGATIVO (ERROR EN CONSUMO)";
        } else if (productos[i].stockFinal < UMBRAL_STOCK_BAJO) {
            productos[i].estado = "ALERTA: STOCK BAJO";
        } else {
            productos[i].estado = "ESTADO: OK";
        }
    }
}

// Módulo de Salida: Función que genera el reporte final de inventario
void mostrarReporte(Producto productos[], int cantidad) {
    cout << "\n==========================================" << endl;
    cout << "       REPORTE FINAL DE INVENTARIO        " << endl;
    cout << "==========================================" << endl;
    cout << left << setw(15) << "PRODUCTO" 
         << setw(15) << "STOCK INICIAL" 
         << setw(15) << "CONSUMO" 
         << setw(15) << "STOCK FINAL" 
         << "ESTADO" << endl;
    cout << "==========================================" << endl;
    
    for (int i = 0; i < cantidad; i++) {
        cout << left << setw(15) << productos[i].nombre 
             << setw(15) << fixed << setprecision(1) << productos[i].stockInicial
             << setw(15) << fixed << setprecision(1) << productos[i].consumo
             << setw(15) << fixed << setprecision(1) << productos[i].stockFinal
             << productos[i].estado << endl;
    }
    
    cout << "==========================================" << endl;
    
    // Mostrar productos con stock bajo
    cout << "\nPRODUCTOS CON STOCK BAJO ( < " << UMBRAL_STOCK_BAJO << " ):" << endl;
    bool hayStockBajo = false;
    for (int i = 0; i < cantidad; i++) {
        if (productos[i].stockFinal < UMBRAL_STOCK_BAJO && productos[i].stockFinal >= 0) {
            cout << "- " << productos[i].nombre << " (Stock: " 
                 << fixed << setprecision(1) << productos[i].stockFinal << ")" << endl;
            hayStockBajo = true;
        }
    }
    
    if (!hayStockBajo) {
        cout << "Todos los productos tienen stock suficiente." << endl;
    }
}

int main() {
    cout << "==========================================" << endl;
    cout << "  SISTEMA DE GESTIÓN DE INVENTARIOS      " << endl;
    cout << "     PARA COMEDORES POPULARES            " << endl;
    cout << "==========================================" << endl;
    
    // Módulo de Entrada: Capturar el número de ítems
    int cantidadProductos;
    cout << "Ingrese la cantidad de productos a registrar: ";
    cin >> cantidadProductos;
    
    // Validar cantidad de productos
    while (cantidadProductos <= 0) {
        cout << "Error: Debe ingresar al menos 1 producto. Intente nuevamente: ";
        cin >> cantidadProductos;
    }
    
    // Crear arreglo de productos
    Producto productos[cantidadProductos];
    
    // Capturar información de cada producto
    cout << "\n--- REGISTRO DE PRODUCTOS ---" << endl;
    for (int i = 0; i < cantidadProductos; i++) {
        cout << "\nProducto " << i + 1 << ":" << endl;
        
        cout << "Nombre del producto: ";
        cin.ignore(); // Limpiar el buffer
        getline(cin, productos[i].nombre);
        
        productos[i].stockInicial = leerValidarDato("Stock inicial (kg/unidades): ");
        productos[i].consumo = leerValidarDato("Cantidad consumida: ");
    }
    
    // Procesar el inventario
    procesarInventario(productos, cantidadProductos);
    
    // Mostrar reporte
    mostrarReporte(productos, cantidadProductos);
    
    cout << "\n--- FIN DEL PROGRAMA ---" << endl;
    
    return 0;
}