//
//  Directories.h
//  CPMA
//
//  Copyright © 2017 Juan Ortiz and Andrés Buelva. All rights reserved.
//

#ifndef Directories_h
#define Directories_h

#include <ftw.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int list(const char *name, const struct stat *status, int type);
int list2(const char *name, const struct stat *status, int type);
int recursiveList(char* path, char* out, int x);

#endif /* Directories_h */


