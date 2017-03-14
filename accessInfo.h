//
//  accessInfo.h
//  CPMA
//
//  Copyright © 2017 Juan Ortiz and Andrés Buelva. All rights reserved.
//

#ifndef accessInfo_h
#define accessInfo_h

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <time.h>
#include <sys/stat.h>

#include <pwd.h>
#include <grp.h>

#include <sys/types.h>

int ObtainInfo (const char *path, int x, FILE *fp);
char* obtenerString(char* path);
void informacion(char *path, int *contador, int *nroDeArchivos);

#endif /* accessInfo_h */
