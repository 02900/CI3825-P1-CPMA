//
//  main.c
//  CPMA
//
//  Copyright © 2017 Juan Ortiz and Andrés Buelva. All rights reserved.
//

#include <stdio.h>
#include "crearProcesos.h"

/*
Funcion principal donde se ejecutara el programa
Entrada argc: Numero de argumenos
Entrada argv: Parametro introducido por pantalla
Salida: un entero que garantiza la salida del programa
*/
int main (int argc, char* argv[])
{
    if(argc != 2)
        printf("Debe introducir un nombre para los archivos de reporte");
    else
        forkear(argv[1]);
    return 0;
}
