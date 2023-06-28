#include "arbol.h"

static Node* CreaNodo(char letra){
    Node *newp;
    if((newp=(Node*)malloc(sizeof(Node)))==NULL)
        return NULL;
    newp->es_palabra=false;
    newp->letra=letra;
    newp->hijos=NULL;
    newp->next=NULL;
    return newp;
}

static bool busca(char letra, Node* dic){
    if (!dic)
        return false;
    if (dic->letra==letra)
        return true;
    return busca(letra,dic->next);
}


static Node* AñadirPalabra(char* palabra, char* significado, Node *dic){
    Node* p=dic,*newp;
    
    for(int i=0;i<strlen(palabra);i++){
        int j=0;
        if(!busca(palabra[i],p)){
            newp=CreaNodo(palabra[i]);
            newp->next=p;
            break;
            for(;newp->letra<p->letra;p=p->next);
        }




    }
    
}