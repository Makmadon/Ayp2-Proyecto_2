#ifndef _ARBOL_H
#define _ARBOL_H
/*Se usa ifndef y define para confirmar si la libreria ya ha sido incluida en el archivo
y no genere problemas, a la hora de compilar el compilador solo la incluira una vez*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*Estructura de la lista enlazada que contendra los significado*/
typedef struct significado{
    char significado[200];
    struct significado *next;
}Significado;

/*Estructura general del arbol trie*/
typedef struct nodo{
    struct nodo* hijos[26];
    bool es_palabra;
    Significado *significado;
}Node;

/*Funciones publicas a usar en el programa principal*/
/*Funcion que recibe el nombre del archivo y crea el TAD diccionario
con la informacion del archivo*/
Node* Cargar(Node* dic, char* N_archivo);
/*Funcion que imprime el significado si la palabra 
se encuentra almacenada, de lo contrario imprime que no se encuentra*/
void Palabra(Node* dic,char *palabra);
/*Funcion que imprime un mensaje de ayuda*/
void help();
/*Imprime todos los significados de palabras que tengan de prefijo el argumento ingresado*/
void Prefijo(Node* dic, char *prefijo);


#endif
