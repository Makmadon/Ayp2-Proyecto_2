all: diccionario diccionario.o arbol.o
arbol.o:  arbol.c
	gcc -c arbol.c
diccionario.o: diccionario.c
	gcc -c diccionario.c
diccionario: arbol.o diccionario.o
	gcc -o main diccionario.o arbol.o
	rm *.o
