//
//  CPMA
//
//  Copyright © 2017 Juan Ortiz and Andrés Buelva. All rights reserved.
//

#ifndef crearProcesos_h
#define crearProcesos_h

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <memory.h>
#include <signal.h>
#include <libgen.h>
#include <string.h>

int forkear (char* salida);

#endif /* crearProcesos_h */
