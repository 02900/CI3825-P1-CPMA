//
//  juan.c
//  CPMA
//
//  Created by Juan Tepedino on 21/2/17.
//  Copyright © 2017 Juan Tepedino. All rights reserved.
//

#include "juan.h"

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

int main (int argc, char *argv[]) {
    if (argc != 1){
        fprintf(stderr, "Ejecute el programa sin introducir parametros");
        return 1;
    }
    
    int dir_count = 0;
    struct dirent* dent;
    
    char cwd[100000];
    getcwd(cwd, sizeof(cwd));           //Mi ruta inicial
    
    DIR* srcdir = opendir(cwd);
    
    if (srcdir == NULL) {
        perror("opendir");
        return -1;
    }
    
    pid_t childpid = 0;
    char* path;                         //ruta de cada hijo
    
    while((dent = readdir(srcdir)) != NULL)
    {
        struct stat st;
        
        if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0)
            continue;
        
        if (fstatat(dirfd(srcdir), dent->d_name, &st, 0) < 0) {
            perror(dent->d_name);
            continue;
        }
        
        // Si hay directorio, imprime nombre, etc
        if (S_ISDIR(st.st_mode)){
            path = concat(cwd, dent->d_name);      //concateno el nombre del directorio inicial con el actual
            dir_count++;
            
            // Creo hijos y les asigno el subdirectorio actual
            if ((childpid = fork()) <= 0) {
                if (chdir(path) == -1) {
                    printf("Failed to change directory: %s\n", strerror(errno));
                    return 0;
                }
                break;
             }
            
            //else
              //  printf("\nSoy padre, debería esperar a mis hijos?");
        }
    }
    
    closedir(srcdir);
    printf("\nEn total encontre %d directorios:\n", dir_count);

    char cwd2[100000];
    getcwd(cwd2, sizeof(cwd2));
    printf("\nMy PID: %d\tMY PPID: %d\nMy path: %s\n",getpid(), getppid(),cwd2);
    
    return 0;
}
