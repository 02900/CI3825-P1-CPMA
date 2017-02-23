all: clean els

# Esta regla compila el programa principal
els: main.o Directories.o check-access.o concatenar.o
	gcc -o els main.o Directories.o check-access.o concatenar.o

main.o: main.c Directories.o
	gcc -c main.c

Directories.o: Directories.h check-access.h concatenar.h
	gcc -c Directories.c check-access.c concatenar.c

clean:
	rm -f els *.o
