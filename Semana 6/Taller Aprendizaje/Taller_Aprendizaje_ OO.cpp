#include <iostream>
#include <vector>
using namespace std;

class Reporte;

class Vehiculo {
protected:
    int id;
    double velocidad;

public:
    Vehiculo(int id, double velocidad) {
        this->id = id;
        this->velocidad = velocidad;
    }

    virtual void moverse() = 0;

    virtual void mostrarInfo() {
        cout << "ID: " << id << " - Velocidad: " << velocidad << endl;
    }

    friend class Reporte;

    virtual ~Vehiculo() {}
};

class Auto : public Vehiculo {
    int puertas;
public:
    Auto(int id, double v, int p) : Vehiculo(id, v) {
        puertas = p;
    }

    void moverse() override {
        cout << "Auto moviendose" << endl;
    }
};

class Drone : public Vehiculo {
    double altura;
public:
    Drone(int id, double v, double a) : Vehiculo(id, v) {
        altura = a;
    }

    void moverse() override {
        cout << "Drone volando" << endl;
    }
};

class Camion : public Vehiculo {
    double carga;
public:
    Camion(int id, double v, double c) : Vehiculo(id, v) {
        carga = c;
    }

    void moverse() override {
        cout << "Camion transportando carga" << endl;
    }
};

template <typename T>
T calcularEficiencia(T consumo, T distancia) {
    return distancia / consumo;
}

class Reporte {
public:
    void mostrar(Vehiculo &v) {
        cout << "Reporte -> ID: " << v.id 
             << " Velocidad: " << v.velocidad << endl;
    }
};

int main() {

    vector<Vehiculo*> lista;

    lista.push_back(new Auto(1, 100, 4));
    lista.push_back(new Drone(2, 70, 300));
    lista.push_back(new Camion(3, 80, 20));

    for (int i = 0; i < lista.size(); i++) {
        lista[i]->moverse();
        lista[i]->mostrarInfo();
    }

    cout << "Eficiencia: "
         << calcularEficiencia(10.0, 200.0)
         << endl;

    Reporte r;
    r.mostrar(*lista[0]);

    for (int i = 0; i < lista.size(); i++) {
        delete lista[i];
    }

    return 0;
}

/*Reflexión Activa.
- ¿Qué ocurre si eliminamos virtual del destructor?
Si quitamos virtual, al borrar un objeto con un puntero a la clase base puede que no se 
ejecute el destructor de la clase hija. Eso puede causar problemas de memoria

- ¿Qué sucede si quitamos override? 
El programa puede compilar igual, pero override nos ayuda a evitar errores si escribimos mal
 el método. Es como una verificación extra

- ¿Qué diferencia existe entre usar punteros y objetos directos?
Con punteros sí funciona el polimorfismo, con objetos directos no se comporta igual y solo 
toma la parte de la clase base */