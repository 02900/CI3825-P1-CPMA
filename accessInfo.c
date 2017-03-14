//
//  accessInfo.c
//  CPMA
//
//  Copyright © 2017 Juan Ortiz and Andrés Buelvas. All rights reserved.
//

#include "accessInfo.h"
#include "concatenar.h"
#include <dirent.h>
#include "concatenar.h"
#include <fcntl.h>

/*Funcion que permite obtener informacion de los directorios y escribirlo en 
un archivo .txt. Si el entero introducido es '0' estamos en presencia de un directorio,
si es '1' estamos en presencia de un archivo .core
Entrada path: String con la ruta del directorio
Entrada x: entero que determina si es un directorio() o un archivo core
Entrada fp: objeto de tipo FILE, para la escritura de la informacion
Salida: entero que determina la finalizacion de la funcion
*/
int ObtainInfo (const char* path, int x, FILE* fp) {
    int rval;
    int nbytes = 0;
    int nroDeArchivos = 0;
    char temp[1000];
    strcpy(temp, path);

    char valor2[100];
    char valor3[100];
    
    // Verifica si se puede (tienen permisos) escribir en la ruta actual, sino imprime mensaje de error
    rval = access (path, W_OK);
    if (errno == EACCES) {
        printf ("/n%sNo se puede escribir (acceso denegado)", path);
        return 1;
    }
    else if (errno == EROFS) {
        printf ("\n%sNo se puede escribir (read-only filesystem)", path);
        return 1;
    }

    struct stat fileStat;				
    if(stat(path,&fileStat) < 0)		
        return 1;						

    /*A partir de aqui se comienza a imprimir por consola la informacion, tambien se escribe en los driectorios correspondientes*/
 
    fprintf(fp, "%s  ", path);
    
    if (x==0){				                                      
        fprintf(fp, (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        fprintf(fp, (fileStat.st_mode & S_IRUSR) ? "r" : "-");
        fprintf(fp, (fileStat.st_mode & S_IWUSR) ? "w" : "-");
        fprintf(fp, (fileStat.st_mode & S_IXUSR) ? "x" : "-");
        fprintf(fp, (fileStat.st_mode & S_IRGRP) ? "r" : "-");
        fprintf(fp, (fileStat.st_mode & S_IWGRP) ? "w" : "-");
        fprintf(fp, (fileStat.st_mode & S_IXGRP) ? "x" : "-");
        fprintf(fp, (fileStat.st_mode & S_IROTH) ? "r" : "-");
        fprintf(fp, (fileStat.st_mode & S_IWOTH) ? "w" : "-");
        fprintf(fp, (fileStat.st_mode & S_IXOTH) ? "x" : "-");
        
        struct passwd *pwd;
        struct group *grp;
        
        pwd = getpwuid(fileStat.st_uid);
        fprintf(fp, " %s ", pwd->pw_name);                      //usuario id
 
        grp = getgrgid(fileStat.st_gid);
        fprintf(fp, " %s  ", grp->gr_name);                     //grupo id
    }

    char buff[20];
    struct tm * timeinfo;
    timeinfo = localtime (&(fileStat.st_mtime));				//fecha modificacion
    
    strftime(buff, 20, "%Y-%m-%d", timeinfo);
    fprintf(fp, "%s ",buff);
    
    if (x==0){				                              		//si es directorio ocurre esto
        timeinfo = localtime (&(fileStat.st_atime));			//fecha acceso
        strftime(buff, 20, "%Y-%m-%d", timeinfo);
        fprintf(fp, " %s ",buff);
        
        informacion(temp, &nbytes, &nroDeArchivos);             //nro de archivos
        sprintf(valor3, "%d", nroDeArchivos); 
        fprintf(fp, " %s ", valor3);

    }
    sprintf(valor2, "%d", nbytes);                              //nro de bytes
    fprintf(fp, " %s \n", valor2);
    return 0;
}

/*
Funcion que permite un string completo con la informacion perteneciente a
una ruta de archivo(directorio): path, grupo id, usuario id, fecha de modificacion,
fecha de acceso, cantidad de bytes, cantidad de archivos.
Entrada paht: string con la ruta del directorio
Salida: string con la informacion recopilada
*/
char* obtenerString(char* path){

    char stringPath[1000]="";
    struct stat fileStat;                
    int nbytes = 0;
    int nroDeArchivos = 0;

    if(stat(path,&fileStat) < 0)        
        exit(0);

    strcat(stringPath, path);
    strcat(stringPath, "  ");

    strcat(stringPath, (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    strcat(stringPath, (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    strcat(stringPath, (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    strcat(stringPath, (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    strcat(stringPath, (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    strcat(stringPath, (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    strcat(stringPath, (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    strcat(stringPath, (fileStat.st_mode & S_IROTH) ? "r" : "-");
    strcat(stringPath, (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    strcat(stringPath, (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    strcat(stringPath, " ");
        
    struct passwd *pwd;
    struct group *grp;
        
    pwd = getpwuid(fileStat.st_uid);
    strcat(stringPath, pwd->pw_name);                           //usuarioid   
    strcat(stringPath, "  ");
        
    grp = getgrgid(fileStat.st_gid);
    strcat(stringPath, grp->gr_name);                           //grupoid
    strcat(stringPath, "  ");

    char buff[20];
    struct tm * timeinfo;
    timeinfo = localtime (&(fileStat.st_mtime));                //fecha modificacion
    
    strftime(buff, 20, "%Y-%m-%d", timeinfo);
    strcat(stringPath, buff);
    strcat(stringPath, "  ");

    timeinfo = localtime (&(fileStat.st_atime));                  //fecha acceso
    strftime(buff, 20, "%Y-%m-%d", timeinfo);

    strcat(stringPath, buff);
    strcat(stringPath, "  ");  

    informacion(path, &nbytes, &nroDeArchivos);
    char valor2[100];
    char valor3[100];
    sprintf(valor2, "%d", nbytes);                              //nro de bytes
    sprintf(valor3, "%d", nroDeArchivos);                       //nro de archivos 

    strcat(stringPath, valor3);
    strcat(stringPath, " ");
    strcat(stringPath, valor2);

    strcat(stringPath, "\n");
    char* retornar = stringPath;
    return retornar;

}

/*
Funcion que permite calcular recursivamente la cantidad de archivos(ficheros 
y directorios) y la cantidad total de bytes de los ficheros o archivos 
pertenecientes a un directorio
Entrada path: ruta del directorios
Entrada *contador: apuntador a la cantidad de bytes
Entrada *contadorArchivos: apuntador a la cantidad de archivos
*/
void informacion(char *path, int *contador, int *contadorArchivos){

    struct dirent* dent;
    DIR* srcdir = opendir(path);
    char *pathArchivo;
    int descriptor;
    char buffer[1000];
    int bytes;

    while((dent = readdir(srcdir)) != NULL)
    {
        char *nombreSubDirectorio = dent->d_name;
        struct stat st;

        if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0)
            continue;
        

        if (fstatat(dirfd(srcdir), dent->d_name, &st, 0) < 0) {
            perror(dent->d_name);
            continue;
        }

        if (S_ISDIR(st.st_mode)){
            char *siguiente = malloc(strlen(nombreSubDirectorio) + strlen(path) +2);
            sprintf(siguiente, "%s/%s", path, nombreSubDirectorio);
            *contadorArchivos = *contadorArchivos +1;
            informacion(siguiente, contador, contadorArchivos);
            free(siguiente);

        }
        else{
            pathArchivo = concat(path, dent->d_name);
            descriptor = open(pathArchivo, O_RDONLY);
            bytes = read(descriptor, buffer, strlen(buffer)+1);
            *contador+= bytes;
            *contadorArchivos = *contadorArchivos +1;
        }

    }
}
