//
//  Directories.h
//  CPMA
//
//  Created by Juan Tepedino on 23/2/17.
//  Copyright © 2017 Juan Tepedino. All rights reserved.
//

#ifndef Directories_h
#define Directories_h

#include <ftw.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int list(const char *name, const struct stat *status, int type);

int recursiveList(char* path, char* out);

#endif /* Directories_h */


