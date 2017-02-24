//
//  main.c
//  CPMA
//
//  Created by Juan Tepedino on 20/2/17.
//  Copyright © 2017 Juan Tepedino. All rights reserved.
//

#include <stdio.h>
#include "juan.h"

int main (int argc, char* argv[])
{
    if(argc != 2)
        printf("Debe introducir un nombre para los archivos de reporte");
    else
        forkear(argv[1]);
    return 0;
}