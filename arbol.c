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
    newp->significado=(char*)malloc(sizeof(char)*(int)strlen(significado));
    strcpy(newp->significado,significado);
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

static void EliminaSignificado(Significado* sig){
    if(!sig)
        return;
    EliminaSignificado(sig->next);
    free(sig->significado);
}

static void* Elimina(Node* dic){
    if(!dic){
        return;
    }
    if(dic->es_palabra){
        EliminaSignificado(dic->significado);
    }
    for(int i=0;i<26;i++){
        if(dic->hijos[i]!=NULL)
            Elimina(dic->hijos[i]);
        free(dic->hijos[i]);
    }
    free(dic);
    dic=NULL;
    return;
}

Node* Cargar(Node* dic,char *N_archivo){
    char *palabra,*significado;
    if(dic){
        Elimina(dic);
    }
    FILE *Archivo=fopen(N_archivo,"r");
    if(!Archivo){
        printf("\nError al abrir archivo\n");
        return NULL;
    }
    while ((fscanf(N_archivo,"%s",palabra))!=EOF)
    {
        
    }
    

}

