#include <iostream>
using namespace std;

class Celular
{
private:
    string marca;
    string modelo;
    int bateria;

public:
    void setMarca(string m)
    {
        marca = m;
    }

    void setModelo(string m)
    {
        modelo = m;
    }

    void setBateria(int b)
    {
        if (b >= 0 && b <= 100)
        {
            bateria = b;
        } else {
            cout<<"Valor de bateria invalido"<<endl;
        }
    }

    string getMarca() const
    {
        return marca;
    }

    string getModelo() const
    {
        return modelo;
    }

    int getBateria() const
    {
        return bateria;
    }

    void mostrarInfo()
    {
        cout << marca << " - " << modelo << " - " << bateria << "%" << endl;
    }
};

int main()
{
    Celular cel;

    cel.setMarca("Samsung");
    cel.setModelo("S23");
    cel.setBateria(150); // invalidooouu
    cel.setBateria(90);  // validooou

    cel.mostrarInfo();

    return 0;
}
/* Reflexión: ¿Qué problema evita el encapsulamiento?
El encapsulamiento sirve para que no cambien los datos asi noma
Hace que los atributos estén protegidos y que solo se puedan modificar de forma controlada
para evitar errores como poner la batería en 200%   */
