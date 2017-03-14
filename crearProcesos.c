//
//  CPMA
//
//  Copyright © 2017 Juan Ortiz and Andrés Buelvas. All rights reserved.
//

#include "crearProcesos.h"
#include "Directories.h"
#include "concatenar.h"
#include "accessInfo.h"
#include <sys/wait.h>

/*Funcion que permite crear los procesos hijos y establecer lo pipes entre
padre e hijos. Ademas aqui se revisan los subdirectorios y se generan los
distintos de reportes solicitados
Entrada salida: Entrada con la rusta o directorio solicitado a buscar
                la informacion
Salida: entero que indica la finalizacion de la funcion correctamente
*/
int forkear (char* salida) {
    signal(SIGINT, SIG_IGN);

    int dir_count = 0;
    struct dirent* dent;

    pid_t childpid = 0;                             //pid del hijo
    char* path = NULL;                              //ruta de cada hijo
    char* out = NULL;                               //nombre base para archivo reporte de cada hijo
    char* outPadre;                          //nombre base para archivo reporte de cada hijo

    char cwd[1000];
    char cwdOri[1000];
    getcwd(cwd, sizeof(cwd));                       //Mi ruta temporal
    getcwd(cwdOri, sizeof(cwdOri));                 //Mi ruta original

    char* ts= strdup(cwd);
    char* absPath = basename(ts);
    char* aux = NULL;
    aux = concat ("/tmp", salida);
    outPadre = concat2(aux, absPath);            //nombre de archivo base + nombre de directorio
    FILE* fp = fopen (outPadre, "a");
    DIR* srcdir = opendir(cwd);

    int p2[2];
    int nbytes;

    char* palabra = "";
    char mensaje [1000] = " ";
    char mensaje2 [1000] = "";
    char* tmp;
    tmp = obtenerString (cwdOri);
    strcat (mensaje2, tmp);

    if (srcdir == NULL) {
        perror("opendir");
        return -1;
    }

    //Recorro directorios mientras todavia queden
    while((dent = readdir(srcdir)) != NULL)
    {
        pipe(p2);
        struct stat st;

        if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0)
            continue;

        if (fstatat(dirfd(srcdir), dent->d_name, &st, 0) < 0) {
            perror(dent->d_name);
            continue;
        }
        // Si es un directorio entonces crea hijo y le asigna directorio de trabajo
        if (S_ISDIR(st.st_mode)){
            path = concat(cwd, dent->d_name);                  //el nombre del directorio inicial + actual
            out = concat2(aux, dent->d_name);               //nombre de archivo base + nombre de directorio

            dir_count++;

            childpid = fork();                                 //crea hijo

            if (childpid == -1) {
                perror("fork failure");
                exit(EXIT_FAILURE);
            }

            //Hijos
            else if (childpid == 0) {
                if (chdir(path) == -1) {
                    printf("Failed to change directory: %s\n", strerror(errno));
                    return 1;
                }
                palabra = obtenerString(path);                //Obtenemos la informacion del hijo

                //Cerramos el lado de lectura del pipe para comenzar a escribir
                close(p2[0]);
                write(p2[1], palabra, strlen(palabra)+1);

                break;
             }

            //Padre
            else {
                waitpid(-1, NULL, 0);

                //Cerramos el lado de escritura del pipe para comenzar a leer
                close(p2[1]);
                nbytes = read(p2[0], mensaje, sizeof(mensaje));
                strcat(mensaje2, mensaje);
            }
        }
    }

    closedir(srcdir);

    getcwd(cwd, sizeof(cwd));
    if (strcmp(cwd, cwdOri) != 0){                    //hijo
        recursiveList(cwd, out, 0);                   //ve a la funcion que recorrera la ruta de trabajo del proceso
    }
    else {                                            //padre
        recursiveList(cwd, outPadre, 1);              //solo elimina y registra los archivos .core de este directorio, no inicia recursion!
        fprintf(fp, "%s",mensaje2);
        fclose(fp);                                   //elimina y registra los archivos .core de este directorio
    }

    exit(0);
    return 0;
}
