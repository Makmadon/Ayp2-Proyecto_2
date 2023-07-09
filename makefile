all: main diccionario.o arbol.o
arbol.o:  arbol.c
	gcc -c arbol.c
diccionario.o: diccionario.c
	gcc -c diccionario.c
main: arbol.o diccionario.o
	gcc -o main diccionario.o arbol.o
