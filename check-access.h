//
//  check-access.h
//  CPMA
//
//  Created by Juan Tepedino on 23/2/17.
//  Copyright © 2017 Juan Tepedino. All rights reserved.
//

#ifndef check_access_h
#define check_access_h

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <time.h>
#include <sys/stat.h>

#include <pwd.h>
#include <grp.h>

int ObtainInfo (const char* path, int x);

#endif /* check_access_h */
