//
//  concatenar.c
//  CPMA
//
//  Copyright © 2017 Juan Ortiz and Andrés Buelvas. All rights reserved.
//

#include "concatenar.h"

/*
Funcion que dado dos string, los concatena a a traves de un "/". Sirve para
armar rutas de archivos.
Entrada str1: ruta de archivo de tipo string
Entrada str3: ruta de archivo de tipo string
Salida: path o ruta concatenada
*/
char* concat (char* str1, char* str3) {
    char c = '/';
    
    size_t len = strlen(str1);
    char *str2 = malloc(len + 1 + 1 ); 
    strcpy(str2, str1);
    str2[len] = c;
    str2[len + 1] = '\0';
    
    char * str4 = (char *) malloc(1 + strlen(str2)+ strlen(str3) );
    strcpy(str4, str2);
    strcat(str4, str3);
    
    free(str2);
    return str4;
}

/*
Funcion que dado dos string, los concatena a a traves de un "-".
Entrada str1: ruta de archivo de tipo string
Entrada str3: ruta de archivo de tipo string
Salida: path o ruta concatenada
*/
char* concat2 (char* str1, char* str3) {
    char c = '-';
    
    size_t len = strlen(str1);
    char *str2 = malloc(len + 1 + 1 );
    strcpy(str2, str1);
    str2[len] = c;
    str2[len + 1] = '\0';
    
    char * str4 = (char *) malloc(1 + strlen(str2)+ strlen(str3) );
    strcpy(str4, str2);
    strcat(str4, str3);
    
    free(str2);
    return str4;
}