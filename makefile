all: clean els

# Esta regla compila el programa principal
els: main.o crearProcesos.o concatenar.o Directories.o accessInfo.o
	gcc -o els main.o crearProcesos.o concatenar.o Directories.o accessInfo.o

main.o: main.c crearProcesos.h concatenar.h Directories.h accessInfo.h
	gcc -c main.c

crearProcesos.o: crearProcesos.c concatenar.h Directories.h accessInfo.h
	gcc -c crearProcesos.c

clean:
	rm -f els *.o