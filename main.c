//
//  main.c
//  CPMA
//
//  Created by Juan Tepedino on 20/2/17.
//  Copyright © 2017 Juan Tepedino. All rights reserved.
//

#include <stdio.h>
//#include "moveDirTree.h"
#include <unistd.h>
#include "Directories.h"


int main (int argc, char* argv[])
{
    //pmatch(".", "*.c");
    
    char cwd[100000];
    getcwd(cwd, sizeof(cwd));
    recursiveList(cwd);
    return 0;
}