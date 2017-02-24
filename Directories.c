//
//  Directories.c
//  CPMA
//
//  Created by Juan Tepedino on 23/2/17.
//  Copyright © 2017 Juan Tepedino. All rights reserved.
//

#include "Directories.h"
#include "check-access.h"
//#include "concatenar.h"

//Recursive directory walk
char* salida;

int recursiveList(char* path, char* out) {
    salida = out;
    ftw(path, list, 1); //sustituir por path al final
    return 0;
}

int list(const char *name, const struct stat *status, int type) {
    FILE* fp = fopen (salida, "a");

    if(type == FTW_NS)
        return 0;
    
    if(type == FTW_DNR)
        return 0;
    
    if(type == FTW_F && strstr(name, "core") != NULL)
        ObtainInfo(name, 1, fp);

    if(type == FTW_D && strcmp(".", name) != 0)
        ObtainInfo(name, 0, fp);
    
    fclose(fp);
    return 0;
}

// FTW_F    The object is a  file
// FTW_D    ,,    ,,   ,, ,, directory
// FTW_DNR  ,,    ,,   ,, ,, directory that could not be read
// FTW_SL   ,,    ,,   ,, ,, symbolic link
// FTW_NS   The object is NOT a symbolic link and is one for
//          which stat() could not be executed