/*
* ABM de arboles
*
* Crear un programa que permita, agregar, eliminar y modificar datos de Arboles, donde los datos relevantes son
* nombre de la especie, edad estimada y altura del árbol. Se sabe que como mucho se trabajara con 100 árboles.
* Inicialmente se deben cargar los datos guardados en un archivo arboles.txt, los datos iniciales son
* (Especie+edad+altura):
*/

#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

// Estructura principal
struct _arbol;
typedef struct _arbol *Arbol;

// constructores
Arbol crearArbol(char espec[],int ed,float alt);
/*
* prepara la lista para ingresar arboles
* Si ya existen previamente (en un archivo de texto arboles.txt) los ingresa a la lista
*/

void prepararListaArboles(Arbol a[],int tam); // prepara la lista para ingresar arboles

void agregarArbol(Arbol a[],int tam,char espec[],int ed,float alt); // ingreasar arboles a la lista

// operaciones varias

void mostrarArbol(Arbol a[],int pos,char leyenda[]);
void mostrarArboles(Arbol a[],int tam);

void modificarArbol(Arbol a[],int tam,char espec[]); //Modifica los datos por teclado, el nombre no se modifica

void eliminarArbol(Arbol a[],int tam,char espec[]);


// operaciones especiales para trabajar con archivos
Arbol procesarRegistro(char str[],char delimit); // analiza un texto y devuelve un arbol

int ingresarArbolesTxt(Arbol arb[],int tam);

int guardarArbolesTxt(Arbol a[],int tam);

#endif // ARBOL_H_INCLUDED
