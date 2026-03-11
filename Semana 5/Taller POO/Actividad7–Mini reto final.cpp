#include <iostream>
#include <string>
using namespace std;

class Vehiculo
{
protected:
    string marca;
    int velocidadMax;

public:
    Vehiculo(string marca, int velocidadMax)
    {
        this->marca = marca;
        this->velocidadMax = velocidadMax;
    }

    void mostrarInfo()
    {
        cout<<"Marca: "<< marca<<endl;
        cout<<"Velocidad Maxima: "<<velocidadMax<<" km/h"<<endl;
    }
};

class Carro : public Vehiculo
{
private:
    int puertas;

public:
    Carro(string marca, int velocidadMax, int puertas)
        : Vehiculo(marca, velocidadMax){
        this->puertas = puertas;
    }

    void mostrarInfo()
    {
        Vehiculo::mostrarInfo();
        cout<< "Puertas: "<<puertas<<endl;
        cout<< endl;
    }
};

class Moto : public Vehiculo
{
private:
    int cilindraje;

public:
    Moto(string marca, int velocidadMax, int cilindraje)
        : Vehiculo(marca, velocidadMax){
        this->cilindraje = cilindraje;
    }

    void mostrarInfo() {
        Vehiculo::mostrarInfo();
        cout<<"Cilindraje: "<< cilindraje<<" cc"<<endl;
        cout<<endl;
    }
};

int main()
{

    Carro c1("Toyota", 180, 4);
    Moto m1("Yamaha", 200, 600);

    c1.mostrarInfo();
    m1.mostrarInfo();

    return 0;
}

/* Reflexión: ¿Por qué la herencia reduce repetición de código?
La herencia ayuda a no repetir lo mismo asi no tenemos que volver a escribir atributos 
como marca o velocidad en cada claseee  */