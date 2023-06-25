#ifndef _ARBOL
#define _ARBOL
#include <stdbool.h>


typedef struct nodo{
    struct nodo* hijos,*next;
    bool es_palabra;
    char letra;
    char *significado;
}Node;




#endif