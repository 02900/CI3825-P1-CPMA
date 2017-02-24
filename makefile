all: clean els

# Esta regla compila el programa principal
els: main.o juan.o concatenar.o Directories.o check-access.o
	gcc -o els main.o juan.o concatenar.o Directories.o check-access.o

main.o: main.c juan.h concatenar.h Directories.h check-access.h
	gcc -c main.c

juan.o: juan.c concatenar.h Directories.h check-access.h
	gcc -c juan.c

clean:
	rm -f els *.o