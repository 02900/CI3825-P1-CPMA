//
//  juan.c
//  CPMA
//
//  Created by Juan Tepedino on 21/2/17.
//  Copyright © 2017 Juan Tepedino. All rights reserved.
//

#include "juan.h"
#include "Directories.h"
#include "concatenar.h"


int forkear (char* salida) {
    
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
    char* path = NULL;                         //ruta de cada hijo
    char* out = NULL;                         //ruta de cada hijo
    
    //Recorro directorios
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
            
            path = concat(cwd, dent->d_name);  //concateno el nombre del directorio inicial con el actual
            out = concat2(salida, dent->d_name);  //concateno el nombre del directorio inicial con el actual

            dir_count++;
            
            childpid = fork();
            
            if (childpid == -1) {
                perror("fork failure");
                exit(EXIT_FAILURE);
            }
            
            // Creo hijos y les asigno el subdirectorio actual
            else if (childpid == 0) {
                //printf("\n%s", out);
                if (chdir(path) == -1) {
                    printf("Failed to change directory: %s\n", strerror(errno));
                    return 0;
                }
                break;
             }
            
            else {
                waitpid(-1, NULL, 0);
                out = salida;
            }
        }
    }
    closedir(srcdir);
    
    getcwd(cwd, sizeof(cwd));
    printf("\n%s", cwd);
    printf("\n%s", out);
    //recursiveList(cwd, out);

    exit(0);
    return 0;
}
