#include "arbol.h"
#define max_palabra 10
#define max_definicion 200
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

static Significado* CreaSignificado(char *significado){
    Significado *newp;
    newp=(Significado*)malloc(sizeof(Significado));
    newp->next=NULL;
    newp->significado=(char*)malloc(sizeof(char)*(int)strlen(significado));
    strcpy(newp->significado,significado);
    return newp;
}

static Significado *AñadeSignificado(char *significado, Significado* list){
    Significado *newp=CreaSignificado(significado);
    newp->next=list;
    return newp;
}

static Node* AñadirPalabra(char* palabra, char* significado, Node* dic){
    Node* p;
    int indice;
    if(!dic)
        dic=CreaNodo();
    p=dic;
    for(int i=0;i<strlen(palabra);i++){
        indice=indice(palabra[i]);
        
        if (p->hijos[indice] == NULL){
            p->hijos[indice]=CreaNodo;
        }else
        p=p->hijos[indice];
    }
    p->es_palabra=1;
    p->significado->significado=AñadeSignificado(significado,p->significado->significado);
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
    char palabra[max_palabra],significado[max_definicion],anterior[max_palabra];
    if(dic){
        Elimina(dic);
    }
    FILE *Archivo=fopen(strcat(N_archivo,".dic"),"r");
    if(!Archivo){
        printf("\nError al abrir archivo\n");
        return NULL;
    }
    while ((fscanf(N_archivo,"%s",palabra))!=EOF)
    {
        fgets(significado,max_definicion,N_archivo);
        if(palabra=='+'){
            dic=AñadirPalabra(anterior,significado,dic);
        }else{
            dic=AñadirPalabra(palabra,significado,dic);
            strcpy(anterior,palabra);
        }

    }
    

}

