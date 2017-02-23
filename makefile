all: clean els

# Esta regla compila el programa principal
els: main.o moveDirTree.o concatenar.o
	gcc -o els main.o moveDirTree.o check-access.o concatenar.o

main.o: main.c moveDirTree.o
	gcc -c main.c

moveDirTree.o: moveDirTree.h check-access.h concatenar.h
	gcc -c moveDirTree.c check-access.c concatenar.c

clean:
	rm -f els *.o
