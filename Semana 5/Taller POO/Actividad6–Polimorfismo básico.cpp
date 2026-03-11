#include <iostream>
#include <string>
using namespace std;

class Persona
{
public:
    virtual void rol()
    {
        cout << "Soy una persona" << endl;
    }
};

class Estudiante : public Persona
{
public:
    void rol() override
    {
        cout << "Soy estudiante" << endl;
    }
};

class Profesor : public Persona
{
public:
    void rol() override
    {
        cout << "Soy profesor" << endl;
    }
};

int main()
{
    Persona* personas[2];
    personas[0] = new Estudiante();
    personas[1] = new Profesor();

    for (int i = 0; i < 2; i++) {
        personas[i]->rol();
    }
}
/*Reflexión: ¿Que ventaja da el polimorfismo
El polimorfismo hace que un mismo método funcione diferente dependiendo del objeto
asi el código es más flexible y se puede usar para varias cosasss */