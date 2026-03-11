#include <iostream>
#include <string>
using namespace std;

class Celular {
private:
    string marca;
    string modelo;
    int bateria;

public:
    void setMarca(string marca)
    {
        this->marca = marca;
    }

    void setModelo(string modelo)
    {
        this->modelo = modelo;
    }

    void setBateria(int bateria)
    {
        if (bateria >= 0 && bateria <= 100) {
            this->bateria = bateria;
        } else {
            cout << "Bateria invalida" << endl;
        }
    }

    // Método para mostrar datos
    void mostrarInfo()
    {
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Bateria: " << bateria << "%" << endl;
    }
};

int main()
{

    Celular cel;

    cel.setMarca("Samsung");
    cel.setModelo("S23");
    cel.setBateria(85);

    cel.mostrarInfo();

    return 0;
}

/* Reflexión: ¿Qué pasaría si no usas this-> cuando el nombre del parámetro 
y el atributo son iguales?
Si no usamos this-> el programa no sabría si hablamos del atributo o del parámetro porque 
se llaman igual
this-> sirve para decir que estamos usando el atributo del objeto.
*/