#include <iostream>
using namespace std;

class Celular
{
public:
    string marca;
    string modelo;
    int bateria;

    void mostrarInfo()
    {
        cout<<"Marca: "<< marca<<endl;
        cout<<"Modelo: "<< modelo<<endl;
        cout<<"Bateria: "<< bateria<<"%"<< endl;
        cout<<endl;
    }
};

int main()
{
    Celular cel1;
    cel1.marca = "Samsung";
    cel1.modelo = "A54";
    cel1.bateria = 80;

    Celular cel2;
    cel2.marca = "Xiaomi";
    cel2.modelo = "Redmi Note";
    cel2.bateria = 65;

    cel1.mostrarInfo();
    cel2.mostrarInfo();

    return 0;
}
/* Reflexión: ¿Qué significa decir que un objeto es una “instancia” de una clase?
Un objeto es algo que se crea a partir de una clase, la clase es como un molde o modelo
y el objeto es el resultado que se hace con ese mole, pero con sus propios datos */
