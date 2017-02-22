#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <memory.h>


int concat (char* str1, char* str3) {

    char c = '/';

    size_t len = strlen(str1);
    char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
    strcpy(str2, str1);
    str2[len] = c;
    str2[len + 1] = '\0';

    char * str4 = (char *) malloc(1 + strlen(str2)+ strlen(str3) );
    strcpy(str4, str2);
    strcat(str4, str3);
    printf("\n%s", str4);

    free(str2);
    return 0;


 }

int main()
{
    int dir_count = 0;
    struct dirent* dent;

    char cwd[100000];
    getcwd(cwd, sizeof(cwd));

    printf("%s\n", cwd);

    DIR* srcdir = opendir(cwd);

    if (srcdir == NULL)
    {
        perror("opendir");
        return -1;
    }

    while((dent = readdir(srcdir)) != NULL)
    {
        struct stat st;

        if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0)
            continue;

        if (fstatat(dirfd(srcdir), dent->d_name, &st, 0) < 0)
        {
            perror(dent->d_name);
            continue;
        }

        if (S_ISDIR(st.st_mode)){
            printf ("\nnameDIR  %s", dent->d_name);

            concat(cwd, dent->d_name);

            dir_count++;
        } 
    }
    closedir(srcdir);
    printf("\n%d", dir_count);

    printf ("\n");

    return dir_count;
}

//https://en.wikibooks.org/wiki/C_Programming/POSIX_Reference/dirent.h