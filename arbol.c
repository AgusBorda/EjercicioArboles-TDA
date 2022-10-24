/*
* ABM de arboles
*
* Crear un programa que permita, agregar, eliminar y modificar datos de Arboles, donde los datos relevantes son
* nombre de la especie, edad estimada y altura del árbol. Se sabe que como mucho se trabajara con 100 árboles.
* Inicialmente se deben cargar los datos guardados en un archivo arboles.txt, los datos iniciales son
* (Especie+edad+altura):
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"
#define MAX_CHARS 100


// Estructura principal
struct _arbol
{
    char especie[30];
    int edad;
    float altura;
};

// constructores
Arbol crearArbol(char espec[],int ed,float alt)
{
    Arbol auxArbol = malloc(sizeof(struct _arbol));

    strcpy(auxArbol->especie,espec);
    auxArbol->edad = ed;
    auxArbol->altura = alt;

    return auxArbol;
}

/*
* prepara la lista para ingresar arboles
* Si ya existen previamente (en un archivo de texto arboles.txt) los ingresa a la lista
* primero se inicializan todos los elementos, luego se utilizara el valor de edad en -1 para
* filtrar los elementos de la lista que no se utilicen
*/
void prepararListaArboles(Arbol a[],int tam) // prepara la lista para ingresar arboles
{
    // inicializar lista
    for(int i = 0; i < tam; i++)
    {
        a[i] = crearArbol("", -1, -1.00);
    }

    // si existen cargar arboles desde el archivo de texto
    ingresarArbolesTxt(a, tam);



}
void agregarArbol(Arbol a[],int tam,char espec[],int ed,float alt) // ingreasar arboles a la lista, busca primer lugar vacio
{
    int libre = -1;

    for(int i = 0 ; i < tam; i++)
    {
        if (a[i]->edad == -1) // se encontro lugar vacio
        {
            libre = i;
            i = tam;
        }

    }
    a[libre] = crearArbol(espec,ed,alt);

}
// operaciones varias

void mostrarArbol(Arbol a[],int pos,char leyenda[])
{
    printf("%s: %s, edad: %d, Altura: %.2f\n",leyenda, a[pos]->especie,a[pos]->edad,a[pos]->altura);
}

void mostrarArboles(Arbol a[],int tam)
{
    for(int i = 0; i < tam; i++)
    {
        if (a[i]->edad != -1)
        {
            mostrarArbol(a,i, "Especie");
        }
    }
}

void modificarArbol(Arbol a[],int tam,char espec[]) //Modifica los datos por teclado, el nombre no se modifica
{
    int encontrado = -1; // -1 indica no encontrado
// primero encontrar el arbol a modificar
    for (int i = 0; i < tam; i++)
    {
        if(!strcmp(a[i]->especie,espec))
        {
            encontrado = i;
            i = tam;
        }

    }
    if(encontrado != -1)
    {
        mostrarArbol(a,encontrado, "Encontrado");

        printf("ingrese nueva edad: ");
        scanf("%d",&a[encontrado]->edad);

        printf("ingrese nueva altura: ");
        scanf("%f",&a[encontrado]->altura);
    }
}


void eliminarArbol(Arbol a[],int tam,char espec[])
{
    int encontrado = -1; // -1 indica no encontrado
// primero encontrar el arbol a modificar
    for (int i = 0; i < tam; i++)
    {
        if(!strcmp(a[i]->especie,espec))
        {
            encontrado = i;
            i = tam;
        }

    }
    if(encontrado != -1)
    {
        mostrarArbol(a,encontrado, "Eliminar");
        a[encontrado]->edad = -1; // se lo marca como eliminado / disponible
    }
}
/*
* Previamente tiene que existir archivo arboles.txt
* Si se encuentra at¡rchivo devuelve la cantidzd de registros hallados
* en caso de no existir archivo devuelve -1
*/
int ingresarArbolesTxt(Arbol arb[],int tam)
{
    int auxCant = 0;
    char str[MAX_CHARS];
    FILE * arboles = fopen("arboles.txt","r");
    if (arboles == NULL)
    {
        //File no se encuentra
        auxCant = -1;
    }
    else
        // Procesar registros
        while (fgets(str,MAX_CHARS,arboles) != NULL)
        {
            // transforma el contenido de la linea en una estructura arbol
            arb[auxCant] = procesarRegistro(str,'+');
            auxCant++;

        }
    fclose(arboles);

    return auxCant;

}

Arbol procesarRegistro(char str[], char delimit) // analiza un texto y devuelve un arbol
{
// un delimitador por cada atributo
    int d1,d2,d3;
    char especie[30] = "";
    char ed[6] = "";
    char alt[6] = "";

// encontrar 1er delimitador
    for (int i = 0; i < MAX_CHARS; i++)
    {
        if(str[i] == delimit)
        {
            d1 = i;
            i = MAX_CHARS;
        }
    }

    // encontrar 2do delimitador
    for (int i = d1 + 1; i < MAX_CHARS; i++)
    {
        if(str[i] == delimit)
        {
            d2 = i;
            i = MAX_CHARS;
        }
    }

    // encontrar 3er delimitador, en este caso es el char '\0' fin de cadena
    for (int i = d2 + 1; i < MAX_CHARS; i++)
    {
        if(str[i] == '\0')
        {
            d3 = i;
            i = MAX_CHARS;
        }
    }

// Procesar datos y devolver el registro arbol
    // especie
    for(int i = 0; i < d1; i++ )
        especie[i] = str[i];

    // edad
    for(int i = d1 + 1 ; i < d2; i++ )
        ed[i - d1 - 1] = str[i];

    // altura
    for(int i = d2 + 1 ; i < d3; i++ )
        alt[i - d2 - 1] = str[i];

    return crearArbol(especie,atoi(ed),atof(alt));

}



int guardarArbolesTxt(Arbol a[],int tam) // vuelve a crear el archivo de Arboles con lo que contiene el vector
{
    int auxCant = 0;
    char str[MAX_CHARS];
    FILE * arboles = fopen("arboles.txt","w");
    if (arboles == NULL)
    {
        //File no se pudo crear
        auxCant = -1;
    }
    else
        // Procesar registros
        for(int i = 0; i < tam;i++)
            if(a[i]->edad != -1) //no procesar registros sin uso o eliminados
            {
                fprintf(arboles,"%s+%d+%.2f\n",a[i]->especie,a[i]->edad,a[i]->altura);
            }
    fclose(arboles);

    return auxCant;
}

