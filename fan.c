//
//  fan.c
//  CPMA
//
//  Created by Juan Tepedino on 21/2/17.
//  Copyright © 2017 Juan Tepedino. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char *argv[]) {
    pid_t childpid = 0;
    int i, n;

    if (argc != 2){   //check for valid number of command-line arguments
    fprintf(stderr, "Usage: %s processes\n", argv[0]);
    return 1;
    }

    n = atoi(argv[1]);
    for (i = 1; i < n; i++) {
        if ((childpid = fork()) < 0)
            break;
    
        else if (childpid == 0){
            if (chdir("path") == -1) {
                    printf("Failed to change directory: %s\n", strerror(errno));
                    return 0;  /* No use continuing */
            }
        }
    
        else
            printf("\niam the papi");
    }

    char cwd[100000];
    getcwd(cwd, sizeof(cwd));
    printf("\nDirectorio actual\n%s", cwd);

    return 0;
}
