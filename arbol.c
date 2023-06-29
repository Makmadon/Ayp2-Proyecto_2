#include "arbol.h"
#define indice(a) ((int)tolower (a) - 'a')


static Node* CreaNodo(){
    Node *newp;
    newp=(Node*)malloc(sizeof(Node));
    for(int i=0;i<26;i++)
        newp->hijos[i]=NULL;
    newp->es_palabra=false;
    newp->significado->significado=NULL;
    return newp;
}

static *CreaSignificado(char *significado){
    Significado *newp;
    newp=(Significado*)malloc(sizeof(Significado));
    strcpy(newp->significado,significado);
    newp->next=NULL;
    return newp;
}

static Node* AñadirPalabra(char* palabra, char* significado, Node* dic){
    Node* p;
    int indice;
    if(!dic)
        dic=CreaNodo();
    p=dic;
    for(int i=0;i<strlen(palabra);i++){
        if (isalpha(palabra[i]))
            indice=indice(palabra[i]);
        
        if (p->hijos[indice] == NULL){
            p->hijos[indice]=CreaNodo;
        }else
        p=p->hijos[indice];
    }
    p->es_palabra=1;
    strcpy(p->significado->significado,significado);
    return dic;
}   



