#include "arbol.h"

Node *dic;

char opcion[20];

int main(){

while (1)
{
    fgets(opcion,20, stdin);
    strtok(opcion,"\n");
    switch (opcion[0])
    {
    case 'q':
        return 0;
    case 'l':
        dic=Cargar(dic,&opcion[2]);
        break;
    case 's':
        Palabra(dic,&opcion[2]);
    case 'p':
        Prefijo(dic,opcion[2]);
    default:
        break;
    }
}
return 0;
}