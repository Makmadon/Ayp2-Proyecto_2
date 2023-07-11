#ifndef _ARBOL_H
#define _ARBOL_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct significado{
    char significado[200];
    struct significado *next;
}Significado;

typedef struct nodo{
    struct nodo* hijos[26];
    bool es_palabra;
    Significado *significado;
}Node;


Node* Cargar(Node* dic, char* N_archivo);

void Palabra(Node* dic,char *palabra);


#endif