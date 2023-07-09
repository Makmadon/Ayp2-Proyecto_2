#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _ARBOL
#define _ARBOL

typedef struct significado{
    char *significado;
    struct significado *next;
}Significado;

typedef struct nodo{
    struct nodo* hijos[26];
    bool es_palabra;
    Significado *significado;
}Node;

Node* Cargar(Node* dic, char* N_archivo);


#endif