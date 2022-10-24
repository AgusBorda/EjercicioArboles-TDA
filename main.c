/*
* Crear un programa que permita, agregar, eliminar y modificar datos de Arboles, donde los datos relevantes son
* nombre de la especie, edad estimada y altura del árbol. Se sabe que como mucho se trabajara con 100 árboles.
* Inicialmente se deben cargar los datos guardados en un archivo arboles.txt, los datos iniciales son
* (Especie+edad+altura):
*/

#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#define MAX_ARBOLES 100

int main()
{
    printf("Ejercicio de Practica: Segundo Parcial Programación\n");

    Arbol arboles[MAX_ARBOLES];

    prepararListaArboles(arboles,MAX_ARBOLES);

    agregarArbol(arboles,MAX_ARBOLES,"Laurel", 210, 2.55);
    agregarArbol(arboles,MAX_ARBOLES,"Secuoya Caucho", 150, 1.99);
    agregarArbol(arboles,MAX_ARBOLES,"Gikgo biloba", 90, 1.88);

    printf("Listar Arboles\n");
    mostrarArboles(arboles,MAX_ARBOLES);

    modificarArbol(arboles,MAX_ARBOLES,"Laurel"); //Modifica los datos por teclado, el nombre no se modifica

    printf("Listar luego de modificar\n");
    mostrarArboles(arboles,MAX_ARBOLES);

    eliminarArbol(arboles,MAX_ARBOLES,"Cocotero");
    eliminarArbol(arboles,MAX_ARBOLES,"Falsa Acacia");

    printf("Listar luego de eliminar\n");
    mostrarArboles(arboles,MAX_ARBOLES);

    guardarArbolesTxt(arboles,MAX_ARBOLES);


    return 0;
}
