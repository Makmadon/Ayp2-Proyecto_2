#include "arbol.h"

static Node* CreaNodo(char letra, char *significado){
    Node *newp;
    if((newp=(Node*)malloc(sizeof(Node)))==NULL)
        return NULL;
    newp->letra=letra;
    strcpy(newp->significado,significado);
    newp->hijos=NULL;
    newp->next=NULL;
    return newp;
}

static Node* AñadirLetra(char letra){

}