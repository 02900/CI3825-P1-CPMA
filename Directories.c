//
//  Directories.c
//  CPMA
//
//  Copyright © 2017 Juan Ortiz and Andrés Buelva. All rights reserved.
//
//Recursive directory walk

#include "Directories.h"
#include "accessInfo.h"

char* salida;

/*
Funcion que dado una ruta de archivo y un entero que especifica que permite
recorrer y listar la informacion de cada carpeta yy de los archivos .core hallados
de manera recursiva. Si el valor del entero es '0', estamos en presencia de un
proceso hijo, si es '1', estamos en presencial del padre
Entrada path: string con la ruta del archivo
Entrada salida: string que sustituira al path 
Entrada x: entero ??
Salida: un entero que indica la finalizacion de la funcion
*/
int recursiveList(char* path, char* out, int x) {
    salida = out;

    if (x == 0)
        ftw(path, list, 1);
    else
        ftw(path, list2, 1);
    
    return 0;
}

/*
Funcion que dado una ruta de archivo, detecta que tipo de archivo es y ejecuta
la acccion correspondiente.
Entrada name: Nombre del archivo
Entrada stat *status: Un apuntador a la estructura stat 
Entrada type: entero que indica el tipo del achivo
Salida: un entero que indica la finalizacion de la funcion
*/
int list(const char *name, const struct stat *status, int type) {
    FILE* fp = fopen (salida, "a");
    int ret=1;
    //Error, no es enlace simbolico ni ninguno ejecutable por stat
    if(type == FTW_NS)
        return 0;
    
    //Es un directorio que no se pudo leer
    if(type == FTW_DNR)
        return 0;
    
    //Enlace simbolico
    if(type == FTW_SL)
        return 0;
    
    //Tipo fichero/archivo
    if(type == FTW_F && strstr(name, "core") != NULL){
        ObtainInfo(name, 1, fp);
    	ret=remove(name);
    }
    // Tipo directorio
    if(type == FTW_D && strcmp(".", name) != 0)
        ObtainInfo(name, 0, fp);
    
    fclose(fp);
    return 0;
}

/*
Funcion que dado una ruta de archivo, detecta que tipo de archivo es y ejecuta
la accion correspondiente. Funcion parecidad a list(), pero esta se ejecuta solo
en los archivos raiz del directorio fuente.
Entrada name: Nombre del archivo
Entrada stat *status: Un apuntador a la estructura stat 
Entrada type: entero que indica el tipo del achivo
Salida: un entero que indica la finalizacion de la funcion
*/
int list2(const char *name, const struct stat *status, int type) {

    FILE* fp = fopen (salida, "a");
    int ret=1;
    //Error, no es enlace simbolico ni ninguno ejecutable por stat
    if(type == FTW_NS)
        return 0;
    
    //Es un directorio que no se pudo leer
    if(type == FTW_DNR)
        return 0;
    
    //Enlace simbolico
    if(type == FTW_SL)
        return 0;
    
    //Tipo fichero/archivo
    if(type == FTW_F && strstr(name, "core") != NULL){
        ObtainInfo(name, 1, fp);
        ret=remove(name);
    }

    fclose(fp);
    return 0;
}