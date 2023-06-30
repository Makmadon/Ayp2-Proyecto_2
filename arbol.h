#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

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

static Node* CreaNodo();

static Significado* CreaSignificado(char *significado);

static Significado *AñadeSignificado(char *significado, Significado* list);

static Node* AñadirPalabra(char* palabra, char* significado, Node* dic);

static void EliminaSignificado(Significado* sig);

static void* Elimina(Node* dic);

Node* Cargar(Node* dic, char* N_archivo);



#endif