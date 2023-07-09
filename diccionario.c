#include "arbol.h"

Node *dic;
char opcion[10];

int main(){

while (1)
{
    scanf("%s", opcion);
    if(opcion[0]=='q')
        break;
    if(opcion[0]=='l')
        dic=Cargar(dic,&opcion[2]);
}

return 0;
}