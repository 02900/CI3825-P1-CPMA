//
//  moveDirTree.h
//  CPMA
//
//  Created by Juan Tepedino on 20/2/17.
//  Copyright © 2017 Juan Ortiz and Andrés Buelva. All rights reserved.
//

#ifndef moveDirTree_h
#define moveDirTree_h

#include <sys/types.h>
#include <err.h>
#include <errno.h>
#include <fnmatch.h>
#include <fts.h>
#include <string.h>
#include <stdio.h>

/* Compare files by name. */
int entcmp(const FTSENT **a, const FTSENT **b);
void pmatch(char *dir, const char *pattern);

#endif /* moveDirTree_h */
//no se utiliza