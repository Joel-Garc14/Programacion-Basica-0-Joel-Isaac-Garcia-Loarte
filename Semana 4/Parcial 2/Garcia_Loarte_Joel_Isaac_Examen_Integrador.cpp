/*
==================== BITÁCORA IA ====================
Herramienta IA usada: ChatGPT
Objetivo del uso: (ej. entender punteros, revisar bug, mejorar diseño)

Preguntas que hice a la IA (resumen):
1. Cómo puedo organizar libros y usuarios usando struct en C++ ?!
2) Cómo hacer una función para buscar un libro por ID ?!
3) Cómo hacer que el menú se repita hasta que el usuario elija salir ?!

Qué sugerencias acepté y por qué:
-Usar struct para agrupar los datos del libro y del usuario,
  porque así el código queda más claro y ordenado
- Usar arreglos normales con un contador, porque es más simple
  por que lo vismos clase

Qué sugerencias rechacé y por qué:
- Me sugirió hacer el programa usando memoria dinámica para que el arreglo 
  creciera automáticamente, pero decidí usar arreglos de tamaño fijo porque para 
  este trabajo no era necesario hacerlo tan complejo
- También pensé en agregar más validaciones y mensajes más detallados, pero preferí
  dejarlo más sencillo para que el código sea más claro y fácil de explicar

Test manual diseñado por mí:
Entrada (pasos/comandos):
- Opción 1: Agregar Libro
  ID: 1
  Título: El Principito
  Autor: Antoine de Saint-Exupéry
  Año: 1943
- Opción 3: Agregar Usuario
  ID: 10
  Nombre: Carlos
- Opción 4: Prestar Libro
  ID Libro: 1
  ID Usuario: 10
- Opción 2: Listar Libros
Salida esperada:
- El libro debe aparecer como Prestado
- Si intento prestarlo otra vez, debe mostrar que ya está prestado
- Al devolverlo, debe volver a mostrarse como Disponible


Nota de autoría:
Declaro que entiendo el código entregado y puedo explicarlo.
====================================================
*/

#include <iostream>
#include <string>
using namespace std;

struct Libro
{
    int id;
    string titulo;
    string autor;
    int anio;
    bool disponible;
};

struct Usuario
{
    int id;
    string nombre;
};

struct Prestamo
{
    int idLibro;
    int idUsuario;
};

Libro libros[50];
Usuario usuarios[30];
Prestamo prestamos[50];

int cantLibros = 0;
int cantUsuarios = 0;
int cantPrestamos = 0;

void agregarLibro()
{
    cout << "ID: ";
    cin >> libros[cantLibros].id;
    cin.ignore();

    cout << "Titulo: ";
    getline(cin, libros[cantLibros].titulo);

    cout << "Autor: ";
    getline(cin, libros[cantLibros].autor);

    cout << "Anio: ";
    cin >> libros[cantLibros].anio;

    libros[cantLibros].disponible = true;
    cantLibros++;
}

void listarLibros()
{
    for(int i = 0; i < cantLibros; i++)
    {
        cout << "\nID: " << libros[i].id;
        cout << "\nTitulo: " << libros[i].titulo;
        cout << "\nAutor: " << libros[i].autor;
        cout << "\nEstado: ";
        if(libros[i].disponible)
            cout << "Disponible\n";
        else
            cout << "Prestado\n";
    }
}

int buscarLibro(int id)
{
    for(int i = 0; i < cantLibros; i++)
    {
        if(libros[i].id == id)
            return i;
    }
    return -1;
}

int buscarUsuario(int id)
{
    for(int i = 0; i < cantUsuarios; i++)
    {
        if(usuarios[i].id == id)
            return i;
    }
    return -1;
}

void agregarUsuario()
{
    cout << "ID Usuario: ";
    cin >> usuarios[cantUsuarios].id;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, usuarios[cantUsuarios].nombre);

    cantUsuarios++;
}

void prestarLibro()
{
    int idL, idU;
    cout << "ID Libro: ";
    cin >> idL;
    cout << "ID Usuario: ";
    cin >> idU;

    int posL = buscarLibro(idL);
    int posU = buscarUsuario(idU);

    if(posL == -1 || posU == -1)
    {
        cout << "Libro o Usuario no existe\n";
        return;
    }

    if(!libros[posL].disponible)
    {
        cout << "Libro ya prestado\n";
        return;
    }

    prestamos[cantPrestamos].idLibro = idL;
    prestamos[cantPrestamos].idUsuario = idU;
    libros[posL].disponible = false;
    cantPrestamos++;

    cout << "Prestamo realizado\n";
}

void devolverLibro()
{
    int idL;
    cout << "ID Libro a devolver: ";
    cin >> idL;

    for(int i = 0; i < cantPrestamos; i++)
    {
        if(prestamos[i].idLibro == idL)
        {
            int pos = buscarLibro(idL);
            if(pos != -1)
                libros[pos].disponible = true;

            prestamos[i] = prestamos[cantPrestamos - 1];
            cantPrestamos--;
            cout << "Libro devuelto\n";
            return;
        }
    }

    cout << "No existe ese prestamo\n";
}

int main()
{
    int op;

    do{
        cout << "\n1. Agregar Libro";
        cout << "\n2. Listar Libros";
        cout << "\n3. Agregar Usuario";
        cout << "\n4. Prestar Libro";
        cout << "\n5. Devolver Libro";
        cout << "\n0. Salir";
        cout << "\nOpcion: ";
        cin >> op;

        switch(op)
        {
            case 1: agregarLibro(); break;
            case 2: listarLibros(); break;
            case 3: agregarUsuario(); break;
            case 4: prestarLibro(); break;
            case 5: devolverLibro(); break;
        }

    } while(op != 0);

    return 0;
}