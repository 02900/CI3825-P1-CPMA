//
//  concatenar.h
//  CPMA
//
//  Copyright © 2017 Juan Ortiz and Andrés Buelva. All rights reserved.
//

#ifndef concatenar_h
#define concatenar_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

char* concat (char* str1, char* str3);
char* concat2 (char* str1, char* str3);
char* concat3 (const char* str1, const char* str3);

#endif /* concatenar_h */
