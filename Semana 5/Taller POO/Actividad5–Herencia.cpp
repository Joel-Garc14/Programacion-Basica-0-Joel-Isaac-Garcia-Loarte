#include <iostream>
using namespace std;

class Persona
{
private:
    string nombre;
    int edad;

public:
    void setNombre(string nombre)
    {
        this->nombre = nombre;
    }

    void setEdad(int edad)
    {
        if (edad >= 0)
        {
            this->edad = edad;
        } else {
            cout << "Edad invalida" << endl;
        }
    }

    string getNombre()
    {
        return nombre;
    }

    int getEdad()
    {
        return edad;
    }

    void mostrar()
    {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
    }
};

class Estudiante : public Persona
{
private:
    string carrera;

public:
    void setCarrera(string carrera)
    {
        this->carrera = carrera;
    }

    void estudiar()
    {
        cout << "Estoy estudiando..." << endl;
    }
};

class Profesor : public Persona
{
private:
    string materia;

public:
    void setMateria(string materia)
    {
        this->materia = materia;
    }

    void ensenar()
    {
        cout << "Estoy enseñando..." << endl;
    }
};

int main()
{

    Estudiante e;
    e.setNombre("Carlos");
    e.setEdad(20);
    e.setCarrera("Ingenieria");
    e.mostrar();
    e.estudiar();

    cout << "------------------" << endl;

    Profesor p;
    p.setNombre("Ana");
    p.setEdad(45);
    p.setMateria("Matematica");
    p.mostrar();
    p.ensenar();

    return 0;
}
/* Reflexión: ¿Qué atributos y métodos comparten Estudiante y Profesor gracias a Persona?
Estudiante y Profesor comparten los atributos nombre y edad, y el metodo mostrar()
gracias a la clase Persona */