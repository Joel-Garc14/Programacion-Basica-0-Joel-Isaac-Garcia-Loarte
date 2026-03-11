#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <sstream>
#include <cstdlib>
using namespace std;

// === ENUMS ===
enum class Rol { ADMIN, EMPLEADO };
enum class TipoUnidad { UNIDAD, KG };
enum class TipoMovimiento { ENTRADA, SALIDA };

// === UTILIDADES ===
class GestorUI {
public:
    static void color(int c) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); }
    static void titulo(const string& t) { system("cls"); color(11); 
        cout << "========================================\n   " << t << "\n========================================\n"; color(7); }
    static void exito(const string& t) { color(10); cout << "[!] " << t << endl; color(7); Sleep(1000); }
    static void error(const string& t) { color(12); cerr << "[ERROR] " << t << endl; color(7); system("pause"); }
    static string strUnidad(TipoUnidad u) { return (u == TipoUnidad::KG) ? "kg" : "unid"; }
    static string strMov(TipoMovimiento m) { return (m == TipoMovimiento::ENTRADA) ? "ENTRADA" : "SALIDA"; }
};

class Seguridad {
public:
    static string leerPass() {
        string pass; char ch;
        cout << "Clave: ";
        while (true) {
            ch = _getch();
            if (ch == 13) { cout << endl; break; }
            if (ch == 8 && !pass.empty()) { pass.pop_back(); cout << "\b \b"; }
            else { pass += ch; cout << "*"; }
        }
        return pass;
    }
    static string codificar(string p) { for (char& c : p) c += 3; return p; }
    static string decodificar(string p) { for (char& c : p) c -= 3; return p; }
};

// === ENTIDADES ===
class Fecha {
    int d, m, a;
public:
    Fecha(int dia = 1, int mes = 1, int anio = 2000) : d(dia), m(mes), a(anio) {}
    int getDia() const { return d; } 
    int getMes() const { return m; } 
    int getAnio() const { return a; }
};

class Producto {
    string nombre; float stock, precio; TipoUnidad unidad; int stockMinimo;
public:
    Producto() : nombre(""), stock(0), precio(0), unidad(TipoUnidad::UNIDAD), stockMinimo(5) {}
    Producto(string n, float s, float p, TipoUnidad u, int sm) : nombre(n), stock(s), precio(p), unidad(u), stockMinimo(sm) {}
    string getNombre() const { return nombre; }
    float getStock() const { return stock; }
    float getPrecio() const { return precio; }
    TipoUnidad getUnidad() const { return unidad; }
    int getStockMinimo() const { return stockMinimo; }
    void setStock(float s) { stock = s; }
    void setPrecio(float p) { precio = p; }
    void setStockMinimo(int sm) { stockMinimo = sm; }
    void actualizarStock(float cant, TipoMovimiento t) { 
        if (t == TipoMovimiento::ENTRADA) stock += cant; else stock -= cant; 
    }
    bool stockBajo() const { return stock <= stockMinimo; }
};

class Movimiento {
    string producto; TipoMovimiento tipo; float cantidad, total; Fecha fecha;
public:
    Movimiento(string p, TipoMovimiento t, float c, float tot, Fecha f) : producto(p), tipo(t), cantidad(c), total(tot), fecha(f) {}
    string getProducto() const { return producto; }
    TipoMovimiento getTipo() const { return tipo; }
    float getCantidad() const { return cantidad; }
    float getTotal() const { return total; }
    Fecha getFecha() const { return fecha; }
};

// === SISTEMA ===
class SistemaAlmacen {
private:
    vector<Producto> inventario;
    bool ejecutando = true;
    
    int buscarProducto(const string& n) const {
        for (size_t i = 0; i < inventario.size(); i++) 
            if (inventario[i].getNombre() == n) return i;
        return -1;
    }
    
    void guardarInventario() {
        ofstream f("productos.txt");
        for (const auto& p : inventario)
            f << p.getNombre() << " " << p.getStock() << " " << p.getPrecio() << " " 
              << (int)p.getUnidad() << " " << p.getStockMinimo() << endl;
        f.close();
    }
    
    void guardarHistorial(const Movimiento& m) {
        ofstream f("historial.txt", ios::app);
        f << m.getProducto() << " " << GestorUI::strMov(m.getTipo()) << " " << m.getCantidad() 
          << " " << m.getTotal() << " " << m.getFecha().getDia() << " " 
          << m.getFecha().getMes() << " " << m.getFecha().getAnio() << endl;
        f.close();
    }
    
    void cargarInventario() {
        ifstream f("productos.txt");
        if (!f.is_open()) return;
        inventario.clear();
        string n; float s, p; int u, sm;
        while (f >> n >> s >> p >> u >> sm) 
            inventario.emplace_back(n, s, p, (TipoUnidad)u, sm);
        f.close();
    }

public:
    SistemaAlmacen() { cargarInventario(); }
    bool estaEjecutando() const { return ejecutando; }
    void detener() { ejecutando = false; }
    
    void registrarProducto() {
        GestorUI::titulo("NUEVO PRODUCTO");
        string n; cout << "Nombre: "; cin >> n;
        if (buscarProducto(n) != -1) { GestorUI::error("Ya existe"); return; }
        int t; cout << "Unidad (1-Unidad, 2-Kg): "; cin >> t;
        float s, p; cout << "Stock: "; cin >> s; cout << "Precio: S/. "; cin >> p;
        inventario.emplace_back(n, s, p, (t==2)?TipoUnidad::KG:TipoUnidad::UNIDAD, 5);
        guardarInventario();
        GestorUI::exito("Registrado");
    }
    
    void registrarMovimiento(TipoMovimiento tipo) {
        bool entrada = (tipo == TipoMovimiento::ENTRADA);
        GestorUI::titulo(entrada ? "ENTRADA" : "VENTA");
        string n; cout << "Producto: "; cin >> n;
        int i = buscarProducto(n);
        if (i == -1) { GestorUI::error("No encontrado"); return; }
        
        cout << "Stock actual: " << inventario[i].getStock() << " " << GestorUI::strUnidad(inventario[i].getUnidad()) << endl;
        float cant; cout << "Cantidad a " << (entrada?"ingresar":"retirar") << ": "; cin >> cant;
        
        if (!entrada && cant > inventario[i].getStock()) { GestorUI::error("Stock insuficiente"); return; }
        
        inventario[i].actualizarStock(cant, tipo);
        int d,m,a; cout << "Fecha (dd mm aaaa): "; cin >> d >> m >> a;
        Movimiento mov(n, tipo, cant, cant * inventario[i].getPrecio(), Fecha(d,m,a));
        
        guardarInventario();
        guardarHistorial(mov);
        
        if (!entrada) {
            cout << "\n========= TICKET =========\n";
            cout << "Producto: " << n << "\nCantidad: " << cant << " " << GestorUI::strUnidad(inventario[i].getUnidad())
                 << "\nTotal: S/. " << fixed << setprecision(2) << mov.getTotal() << "\n==========================\n";
            system("pause");
        } else GestorUI::exito("Actualizado");
    }
    
    void eliminarProducto() {
        GestorUI::titulo("ELIMINAR");
        string n; cout << "Nombre: "; cin >> n;
        int i = buscarProducto(n);
        if (i == -1) { GestorUI::error("No existe"); return; }
        inventario.erase(inventario.begin() + i);
        guardarInventario();
        GestorUI::exito("Eliminado");
    }
    
    void modificarProducto(bool precioStock) {
        string n; cout << "Producto: "; cin >> n;
        int i = buscarProducto(n);
        if (i == -1) { GestorUI::error("No encontrado"); return; }
        if (precioStock) {
            float p,s; cout << "Nuevo Precio: "; cin >> p; cout << "Nuevo Stock: "; cin >> s;
            inventario[i].setPrecio(p); inventario[i].setStock(s);
        } else {
            int sm; cout << "Nuevo Stock Minimo: "; cin >> sm;
            inventario[i].setStockMinimo(sm);
        }
        guardarInventario();
        GestorUI::exito("Actualizado");
    }
    
    void verInventario() const {
        GestorUI::titulo("INVENTARIO");
        cout << left << setw(15) << "NOMBRE" << setw(10) << "STOCK" << setw(10) << "UNIDAD" << setw(12) << "PRECIO" << "ESTADO\n";
        cout << string(57, '-') << endl;
        for (const auto& p : inventario) {
            cout << left << setw(15) << p.getNombre() << setw(10) << p.getStock() 
                 << setw(10) << GestorUI::strUnidad(p.getUnidad()) << "S/." << setw(9) << fixed << setprecision(2) << p.getPrecio();
            if (p.stockBajo()) { GestorUI::color(12); cout << " [BAJO]"; } 
            else { GestorUI::color(10); cout << " [OK]"; }
            GestorUI::color(7); cout << endl;
        }
        system("pause");
    }
    
    void verHistorial() const {
        GestorUI::titulo("HISTORIAL");
        ifstream f("historial.txt");
        if (!f.is_open()) { GestorUI::error("Sin historial"); return; }
        string p, t; float c, tot; int d,m,a;
        cout << left << setw(12) << "FECHA" << setw(15) << "PRODUCTO" << setw(10) << "TIPO" << setw(10) << "CANT" << "TOTAL\n";
        cout << string(57, '-') << endl;
        while (f >> p >> t >> c >> tot >> d >> m >> a) {
            GestorUI::color(t=="ENTRADA"?10:12);
            cout << d << "/" << m << "/" << a << "   " << left << setw(15) << p << setw(10) << t << setw(10) << c << "S/." << tot << endl;
        }
        GestorUI::color(7); system("pause");
        f.close();
    }
    
    void reporteMensual() const {
        GestorUI::titulo("REPORTE MENSUAL");
        int mes, anio; float total = 0;
        cout << "Mes: "; cin >> mes; cout << "Año: "; cin >> anio;
        ifstream f("historial.txt");
        if (!f.is_open()) { GestorUI::error("Sin historial"); return; }
        string p, t; float c, tot; int d,m,a;
        bool encontrado = false;
        cout << "\n--- Ventas " << mes << "/" << anio << " ---\n";
        while (f >> p >> t >> c >> tot >> d >> m >> a) {
            if (m == mes && a == anio && t == "SALIDA") {
                cout << p << " -> S/." << tot << endl;
                total += tot; encontrado = true;
            }
        }
        cout << string(25, '-') << endl;
        if (encontrado) { GestorUI::color(14); cout << "TOTAL: S/. " << fixed << setprecision(2) << total << endl; } 
        else cout << "Sin ventas\n";
        GestorUI::color(7); system("pause");
        f.close();
    }
};

// === USUARIOS ===
class Usuario {
protected:
    string username, password;
    Rol rol;
public:
    Usuario(string u, string p, Rol r) : username(u), password(p), rol(r) {}
    virtual ~Usuario() = default;
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    virtual void mostrarMenu(SistemaAlmacen& s) = 0;
};

class Administrador : public Usuario {
public:
    Administrador(string u, string p) : Usuario(u, p, Rol::ADMIN) {}
    void mostrarMenu(SistemaAlmacen& s) override {
        int op;
        do {
            GestorUI::titulo("ALMACEN POO");
            cout << "Usuario: " << username << " [ADMIN]\n";
            cout << "1.Registrar\n2.Entrada\n3.Venta\n4.Inventario\n5.Historial\n6.Reporte\n7.Eliminar\n8.Modificar P/S\n9.Stock Min\n10.Salir\nOpcion: ";
            cin >> op;
            switch(op) {
                case 1: s.registrarProducto(); break;
                case 2: s.registrarMovimiento(TipoMovimiento::ENTRADA); break;
                case 3: s.registrarMovimiento(TipoMovimiento::SALIDA); break;
                case 4: s.verInventario(); break;
                case 5: s.verHistorial(); break;
                case 6: s.reporteMensual(); break;
                case 7: s.eliminarProducto(); break;
                case 8: s.modificarProducto(true); break;
                case 9: s.modificarProducto(false); break;
                case 10: s.detener(); break;
            }
        } while (op != 10);
    }
};

class Empleado : public Usuario {
public:
    Empleado(string u, string p) : Usuario(u, p, Rol::EMPLEADO) {}
    void mostrarMenu(SistemaAlmacen& s) override {
        int op;
        do {
            GestorUI::titulo("ALMACEN POO");
            cout << "Usuario: " << username << " [EMPLEADO]\n";
            cout << "1.Registrar\n2.Venta\n3.Inventario\n4.Historial\n5.Reporte\n6.Salir\nOpcion: ";
            cin >> op;
            switch(op) {
                case 1: s.registrarProducto(); break;
                case 2: s.registrarMovimiento(TipoMovimiento::SALIDA); break;
                case 3: s.verInventario(); break;
                case 4: s.verHistorial(); break;
                case 5: s.reporteMensual(); break;
                case 6: s.detener(); break;
            }
        } while (op != 6);
    }
};

class GestorSesion {
    vector<unique_ptr<Usuario>> usuarios;
    
    void cargarUsuarios() {
        ifstream f("usuarios.txt");
        if (!f.is_open()) return;
        string u, p, r;
        while (f >> u >> p >> r) {
            string pass = Seguridad::decodificar(p);
            if (r == "ADMIN") usuarios.push_back(make_unique<Administrador>(u, pass));
            else usuarios.push_back(make_unique<Empleado>(u, pass));
        }
        f.close();
    }
    
    void guardarDefault() {
        ofstream f("usuarios.txt");
        f << "admin " << Seguridad::codificar("admin") << " ADMIN\n";
        f << "vendedor " << Seguridad::codificar("123") << " EMPLEADO\n";
        f.close();
        cargarUsuarios();
    }
    
public:
    GestorSesion() { cargarUsuarios(); if (usuarios.empty()) guardarDefault(); }
    
    Usuario* login() {
        int intentos = 3;
        while (intentos--) {
            GestorUI::titulo("LOGIN");
            string u, p;
            cout << "Usuario: "; cin >> u;
            p = Seguridad::leerPass();
            
            for (const auto& user : usuarios) {
                if (user->getUsername() == u && user->getPassword() == p) {
                    GestorUI::exito("Bienvenido " + u);
                    return user.get();
                }
            }
            GestorUI::error("Credenciales incorrectas. Intentos: " + to_string(intentos));
        }
        return nullptr;
    }
};

// === MAIN ===
int main() {
    SetConsoleOutputCP(CP_UTF8);
    system("title SISTEMA ALMACEN POO");
    
    GestorSesion sesion;
    Usuario* usuarioActual = sesion.login();
    
    if (usuarioActual) {
        SistemaAlmacen sistema;
        usuarioActual->mostrarMenu(sistema);
    }
    
    return 0;
}