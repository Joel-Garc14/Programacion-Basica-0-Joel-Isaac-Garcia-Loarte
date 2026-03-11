#include "Usuarios.h"

int main() {
    SetConsoleOutputCP(CP_UTF8); 
    system("title SISTEMA DE ALMACEN POO"); 
    
    GestorSesion sesion;  // ob
    Usuario* usuarioActual = sesion.login();    //pun

    if (usuarioActual != nullptr) {
        SistemaAlmacen sistema;   //ob
        usuarioActual->mostrarMenu(sistema);  //pun
    }

    return 0;
}