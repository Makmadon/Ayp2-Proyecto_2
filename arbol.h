#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _ARBOL
#define _ARBOL

typedef struct nodo{
    struct nodo* hijos,*next;
    bool es_palabra;
    char letra;
    char *significado;
}Node;

static Node* CreaNodo(char letra);

static bool busca(char letra, Node *dic);

static Node* AñadirPalabra(char* palabra, char *significado, Node *dic);


#endif