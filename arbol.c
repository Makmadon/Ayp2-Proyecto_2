#include "arbol.h"

/*Macro que sera el mensaje de ayuda*/
#define ayuda "Uso:[opcion] [argumento]\n Opciones validas:\n\
l Carga el archivo desde el nombre indicado como argumento con su extension\n\
s Busca el significado de la palabra indicada como argumento\n\
p Imprime todos los significados de las palabras que comienzan con el prefijo\n\
h Muestra este mensaje de ayuda\n\
q Sale de la aplicacion"

/*Se define los tamaños maximo*/
#define max_palabra 15
#define max_definicion 200
/*macro para calcular el indice de las claves para construir el TAD*/
#define indice(a) ((int)tolower (a) - 'a')

 //Funcion que crea un nodo para el diccionario
static Node* CreaNodo(){
    Node *newp;
    if ((newp=(Node*)malloc(sizeof(Node)))==NULL){
        printf("error malloc");
        return NULL;
    }
// asigna NULL a todos los apuntadores del arreglo
    for(int i=0;i<26;i++)
        newp->hijos[i]=NULL;
    newp->es_palabra=false;
    newp->significado=NULL;
    return newp;
}

// Crea un nodo de la estructura que contiene los significados
static Significado* CreaSignificado(char *significado){
    Significado *newp;
    if ((newp=(Significado*)malloc(sizeof(Significado)))==NULL){
        printf("Error en malloc");
        return NULL;
    }
    newp->next=NULL;
    //copia el significado dentro de la estructura
    strcpy(newp->significado,significado);
    return newp;
}

//Añade al inicio de la lista de significados un nuevo significado
static Significado *AñadeSignificado(char *significado, Significado* list){
    Significado *newp=CreaSignificado(significado);
    newp->next=list;
    return newp;
}

//Añade palabras en la estructura
static Node* AñadirPalabra(char* palabra, char* significado, Node* dic){
    Node* p;
    int indice;
//Si el diccionario no existe, se crea
    if(!dic)
        dic=CreaNodo();
// se usa un apuntador para moverse en la estructura, comenzando por la raiz
    p=dic;
// avanza con un contador hasta el final de el largo de la palabra a ingresar
    for(int i=0;i<(int)strlen(palabra);i++){
        //calcula el indice del caracter
        indice=indice(palabra[i]);
        //verifica si el apuntador es nullo, e caso de ser verdadero lo crea y avanza
        if (p->hijos[indice] == NULL)
            p->hijos[indice]=CreaNodo();
        //en caso de que no sea nulo significa que la clave ya existe, por lo que solo avanza
        p=p->hijos[indice];
    }
    //al salir del ciclo es que es el final de la palabra
    //se indica que es la palbra con la bandera y se añade el significado
    p->es_palabra=true;
    p->significado=AñadeSignificado(significado,p->significado);
    return dic;
}
  

//Funcion que hace free a todos los nodos de los significados
static void EliminaSignificado(Significado* sig){
    if(!sig)
        return;
    EliminaSignificado(sig->next);
    free(sig->significado);
    return;
}

//funcion que hace free a todos los nodos del diccionario
static void Elimina(Node* dic){
    if(!dic){
        return;
    }
  //Si es una palabra, se eliminan los significados
    if(dic->es_palabra){
        EliminaSignificado(dic->significado);
    }
 //se recorren todos los elementos del arreglo, si no es nulo, avanza con
 //la funcion elimina haciendo free al nodo
    for(int i=0;i<26;i++){
        if(dic->hijos[i]!=NULL)
            Elimina(dic->hijos[i]);
    }
    free(dic);
    dic=NULL;
    return;
}

//Recibe el nombre del archivo, lo abre y manipula para crear la estructura
Node* Cargar(Node* dic, char *N_archivo){
//se crea el archivo y variables necesarias para las operaciones
    char* file;
    char palabra[max_palabra],significado[max_definicion],anterior[max_palabra];
//Si el diccionario existe, se borra
    if(dic){
        Elimina(dic);
        dic=NULL;
    }
    FILE *Archivo;
//Se abre el archivo
    Archivo=fopen(N_archivo,"r");
//En caso de que el archivo sea nulo, se regresa un error
    if(Archivo==NULL){
        printf("\nError al abrir archivo\n");
        return NULL;
    }
//Se lee la primera palabra, fscanf leera la entrada hasta el primer espacio en blanco
//esta es la palabra a ingresar
    while (fscanf(Archivo,"%s",palabra)!=EOF){
//fgets leera hasta el primer salto de linea, este es el significado
        fgets(significado,max_definicion,Archivo);
//si la palabra leida es el caracter '+' significa que se añade el significado a la palabra anterior
        if(palabra[0]=='+'){
            dic=AñadirPalabra(anterior,significado+1,dic);
        }else{
//de lo contrario se añade la nueva palabra y se copia en la variable 'anterior'
            dic=AñadirPalabra(palabra,significado+1,dic);
            strcpy(anterior,palabra);
        }
    }
//se devuelve el diccionario
return dic;
}


//Fiuncion que busca la lista de significados y la regresa
static Significado *ObtenerSignificados(Node* dic, char *palabra){
    Node* p=dic;
    int indice;
 //recorre de la misma forma que en el asignar
    for(int i=0;i<(int)strlen(palabra);i++){
        indice=indice(palabra[i]);
//en caso de que el arreglo con el indice indique a null
//significa que la palabra no se encuentra en el diccionario
        if (p->hijos[indice] == NULL){
            return NULL;
        }else
        p=p->hijos[indice];
    }
    return p->significado;
}


//Imprime los significados obtenidos de la funcion ObtieneSignificado
void Palabra(Node* dic,char *palabra){
 //la lista de significados es obtenida
    Significado *p=ObtenerSignificados(dic,palabra);
    if(!p)
        printf("No se encuentra en el diccionario\n");
 //En caso de que haya significados, se imprime la palabra buscada al principio
    if(p)
        printf("%s: ",palabra);
 //Se recorre la lista hasta llegar al final imprimiendo los significados
    while (p)
    {
        printf("%s", p->significado);
        p=p->next;
    }
}

//Funcion auxiliar que recorrera toda la estructura, imprimiendo cada significado que encuentre
static void recorre(Node* dic){
    Significado* list;
//confirma si el nodo actual es el final de una palabra, si es correcto, recorrela la lista
    if(dic->es_palabra){
        list=dic->significado;
        while (list)
            {
                printf("%s",list->significado);
                list=list->next;
            }
        }
 //recorre todos los nodos desde el primero hasta el ultimo
 //en caso de encontrar un nodo con hijos, lo recorre tambien
    for(int i=0;i<26;i++){
        if(dic->hijos[i])
            recorre(dic->hijos[i]);
    }
}

//Funcion que imprime el mensaje de ayuda escrito al inicio del programa
void help(){
    printf(ayuda);
}

//Funcion que avanza al nodo que contiene el prefijo indicado
void Prefijo(Node* dic, char *prefijo){
    Node* p;
    Significado* list;
    int indice;
 //Recorre la estructura de la misma forma que al crear y buscar una palabra
    for(int i=0;i<(int)strlen(prefijo);i++){
        indice=indice(prefijo[i]);
 //En caso de que alguno de los nodos buscados no exista, no existe ninguna palabra con ese prefijo
        if (dic->hijos[indice] == NULL){
            printf("No se encuentra en el diccionario\n");
            return ;
        }else
        dic=dic->hijos[indice];
    }
    p=dic;
//Se recorren e imprimen todos los hijos del nodo
    recorre(dic);
        
}
