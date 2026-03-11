#include <iostream>
#include <string>
using namespace std;

class Celular
{
private:
    string marca;
    string modelo;
    int bateria;

public:
    // Constructor por defectouuu
    Celular()
    {
        marca = "Desconocida";
        modelo = "Generico";
        bateria = 100;
    }

    // Constructor con 2 parametrouus
    Celular(string marca, string modelo)
    {
        this->marca = marca;
        this->modelo = modelo;
        bateria = 100;
    }

    // Constructor con 3 parametrouuus
    Celular(string marca, string modelo, int bateria)
    {
        this->marca = marca;
        this->modelo = modelo;
        if (bateria >= 0 && bateria <= 100)
            this->bateria = bateria;
        else
            this->bateria = 100;
    }

    void mostrarInfo()
    {
        cout << marca << " - " << modelo << " - " << bateria << "%" << endl;
    }
};

int main() {
    Celular c1;
    Celular c2("Samsung", "A15");
    Celular c3("Xiaomi", "Note 12", 85);

    c1.mostrarInfo();
    c2.mostrarInfo();
    c3.mostrarInfo();
}
/*Reflexión: ¿Por qué es útil tener constructores sobrecargados?
Es bueno tener varios constructores porque así podemos crear objetos de distintas maneras
 según lo que necesitemos en ese momento */