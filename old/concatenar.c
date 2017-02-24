//
//  concatenar.c
//  CPMA
//
//  Created by Juan Tepedino on 23/2/17.
//  Copyright © 2017 Juan Tepedino. All rights reserved.
//

#include "concatenar.h"


/*Funcion para concatenar strings*/
/*me sirve para armar la ruta absoluta de una carpeta*/
char* concat (char* str1, char* str3) {
    char c = '/';
    
    size_t len = strlen(str1);
    char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
    strcpy(str2, str1);
    str2[len] = c;
    str2[len + 1] = '\0';
    
    char * str4 = (char *) malloc(1 + strlen(str2)+ strlen(str3) );
    strcpy(str4, str2);
    strcat(str4, str3);
    
    free(str2);
    return str4;
}

//no se utiliza