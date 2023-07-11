#include "arbol.h"

Node *dic;

char opcion[20];

int main(){

while (1)
{
    printf("Escriba un comando con su argumento:\n");
    fgets(opcion,20, stdin);
    strtok(opcion,"\n");
   // system("clear");
    switch (opcion[0])
    {
    case 'q':
        return 0;
    case 'l':
        dic=Cargar(dic,&opcion[2]);
        break;
    case 's':
        Palabra(dic,&opcion[2]);
        break;
    case 'p':
        Prefijo(dic,&opcion[2]);
        break;
    case 'h':
        help();
    default:
        break;
    }
}
return 0;
}