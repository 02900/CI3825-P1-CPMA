all: clean els

# Esta regla compila el programa principal
els: main.o moveDirTree.o
	gcc -o els main.o moveDirTree.o

main.o: main.c moveDirTree.o
	gcc -c main.c

moveDirTree.o: moveDirTree.h
	gcc -c moveDirTree.c

clean:
	rm -f els *.o
