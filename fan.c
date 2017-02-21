//
//  fan.c
//  CPMA
//
//  Created by Juan Tepedino on 21/2/17.
//  Copyright © 2017 Juan Tepedino. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

#include <dirent.h>





int es_Directorio(const char *padre, char *hijo){
    
    struct stat s;
    
    if(!strcmp(".", hijo) || !strcmp("..", hijo)){
        return 0;
    }
    
    char *path = malloc(strlen(hijo) + strlen(padre) +2);
    sprintf(path, "%s/%s", padre, hijo);
    stat(path, &s);
    free(path);
    return S_ISDIR(s.st_mode);
}

int crearProcesoHijo(const char* nombreDirectorio){
    
    pid_t procesoHijo;
    DIR *directorio;
    struct dirent *pDirent;
    
    directorio = opendir(nombreDirectorio);
    
    if(directorio == NULL){
        
        printf("Error al abrir el directorio\n");
        return(-1);
    }
    int i =0;
    while((pDirent = readdir(directorio)) != NULL){
        
        char *hijo = pDirent->d_name;
        
        if(es_Directorio(nombreDirectorio, hijo)){
            
            procesoHijo = fork();
            i ++;
            if(procesoHijo == -1){
                perror("Error funcion fork()");
                exit(1);
            }
            
            else if(procesoHijo == 0){
                
                printf("Directorio: %s\n", hijo);
                char *siguiente = malloc(strlen(hijo) + strlen(nombreDirectorio) +2);
                sprintf(siguiente, "%s/%s", nombreDirectorio, hijo);
                crearProcesoHijo(siguiente);
                free(siguiente);
                
                fprintf(stderr, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
                        i, (long)getpid(), (long)getppid(), (long)procesoHijo);
                
                exit(0);

            }
        }
        else{
            //ES FICHERO
            continue;
        }
    }
    
    closedir(directorio);
    return 0;
}



int main (int argc, char *argv[]) {
    /*  pid_t childpid = 0;
     int i, n;
     
     if (argc != 2){   //check for valid number of command-line arguments
     fprintf(stderr, "Usage: %s processes\n", argv[0]);
     return 1;
     }
     n = atoi(argv[1]);
     for (i = 1; i < n; i++)
     if ((childpid = fork()) <= 0)
     //chdir(sj(i));
     break;
     
     char cwd[100000];
     getcwd(cwd, sizeof(cwd));
     

     
     return 0;*/
    
    char cwd[100000];
    getcwd(cwd, sizeof(cwd));
    
    crearProcesoHijo(cwd);
}
