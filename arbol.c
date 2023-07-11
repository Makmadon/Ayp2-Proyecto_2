#include "arbol.h"

#define ayuda "Uso:[opcion] [argumento]\n Opciones validas:\n\
l Carga el archivo desde el nombre indicado como argumento con su extension\n\
s Busca el significado de la palabra indicada como argumento\n\
p Imprime todos los significados de las palabras que comienzan con el prefijo\n\
h Muestra este mensaje de ayuda\n\
q Sale de la aplicacion"

#define max_palabra 15
#define max_definicion 200
#define indice(a) ((int)tolower (a) - 'a')


static Node* CreaNodo(){
    Node *newp;
    if ((newp=(Node*)malloc(sizeof(Node)))==NULL)
        printf("error malloc");
    for(int i=0;i<26;i++)
        newp->hijos[i]=NULL;
    newp->es_palabra=false;
    newp->significado=NULL;
    return newp;
}

static Significado* CreaSignificado(char *significado){
    Significado *newp;
    newp=(Significado*)malloc(sizeof(Significado));
    newp->next=NULL;
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
    for(int i=0;i<(int)strlen(palabra);i++){
        indice=indice(palabra[i]);
        if (p->hijos[indice] == NULL){
            p->hijos[indice]=CreaNodo();
            p=p->hijos[indice];
        }else
        p=p->hijos[indice];
    };
    p->es_palabra=true;
    p->significado=AñadeSignificado(significado,p->significado);
    return dic;
}   

static void EliminaSignificado(Significado* sig){
    if(!sig)
        return;
    EliminaSignificado(sig->next);
    free(sig->significado);
    return;
}

static void Elimina(Node* dic){
    if(!dic){
        return;
    }
    if(dic->es_palabra){
        EliminaSignificado(dic->significado);
    }
    for(int i=0;i<26;i++){
        if(dic->hijos[i]!=NULL)
            Elimina(dic->hijos[i]);
    }
    free(dic);
    dic=NULL;
    return;
}

Node* Cargar(Node* dic, char *N_archivo){
    char* file;
    char palabra[max_palabra],significado[max_definicion],anterior[max_palabra];
    if(dic){
        Elimina(dic);
        dic=NULL;
    }
    FILE *Archivo;
    Archivo=fopen(N_archivo,"r");
    if(Archivo==NULL){
        printf("\nError al abrir archivo\n");
        return NULL;
    }
    while (fscanf(Archivo,"%s",palabra)!=EOF)
    {
        fgets(significado,max_definicion,Archivo);
        if(palabra[0]=='+'){
            dic=AñadirPalabra(anterior,significado+1,dic);
        }else{
            dic=AñadirPalabra(palabra,significado+1,dic);
            strcpy(anterior,palabra);
        }

    }
    
return dic;
}

static Significado *ObtenerSignificados(Node* dic, char *palabra){
    Node* p=dic;
    int indice;
    for(int i=0;i<(int)strlen(palabra);i++){
        indice=indice(palabra[i]);
        if (p->hijos[indice] == NULL){
            printf("No se encuentra en el diccionario\n");
            return NULL;
        }else
        p=p->hijos[indice];
    }
    return p->significado;
}

void Palabra(Node* dic,char *palabra){
    Significado *p=ObtenerSignificados(dic,palabra);
    if(p)
        printf("%s: ",palabra);
    while (p)
    {
        printf("%s", p->significado);
        p=p->next;
    }
}

static int recorre(Node* dic){
    Significado* list;
    if(dic->es_palabra){
        list=dic->significado;
        while (list)
            {
                printf("%s",list->significado);
                list=list->next;
            }
        }
    for(int i=0;i<26;i++){
        if(dic->hijos[i])
            recorre(dic->hijos[i]);
    }
    return 1;
}

void help(){
    printf(ayuda);
}

void Prefijo(Node* dic, char *prefijo){
    Node* p;
    Significado* list;
    int indice;
    for(int i=0;i<(int)strlen(prefijo);i++){
        indice=indice(prefijo[i]);
        if (dic->hijos[indice] == NULL){
            printf("No se encuentra en el diccionario\n");
            return ;
        }else
        dic=dic->hijos[indice];
    }
    p=dic;

    recorre(dic);
        
}
