//
//  moveDirTree.c
//  CPMA
//
//  Created by Juan Tepedino on 20/2/17.
//  Copyright © 2017 Juan Ortiz and Andrés Buelva. All rights reserved.
//

#include "check-access.h"

int ObtainInfo (char* path) {
    char cwd[100000];
    getcwd(cwd, sizeof(cwd));
    
    /*int rval;
    
    // Check file existence.
    rval = access (path, F_OK);
    if (rval == 0)
        printf ("%s exists\n", path);
    else {
        if (errno == ENOENT)
            printf ("%s does not exist\n", path);
        else if (errno == EACCES)
            printf ("%s is not accessible\n", path);
        return 0;
    }
    
    // Check read access.
    rval = access (path, R_OK);
    if (rval == 0)
        printf ("%s is readable\n", path);
    else
        printf ("%s is not readable (access denied)\n", path);
    
    // Check write access.
    rval = access (path, W_OK);
    if (rval == 0)
        printf ("%s is writable\n", path);
    else if (errno == EACCES)
        printf ("%s is not writable (access denied)\n", path);
    else if (errno == EROFS)
        printf ("%s is not writable (read-only filesystem)\n", path);
    
    // Check read access.
    rval = access (path, X_OK);
    if (rval == 0)
        printf ("%s is executable\n", path);
    else
        printf ("%s is not executable (access denied)\n", path);
    */

    //printf("\n%s", cwd);
    
    struct stat fileStat;
    if(stat(cwd,&fileStat) < 0)
        return 1;
    
    printf("Information for %s\n", path);
    printf("---------------------------\n");
    
    //printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    
    //printf("\nThe file %s a symbolic link", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
    printf("  %d ",fileStat.st_nlink); //Number of Links
    
    struct passwd *pwd;
    struct group *grp;
    
    pwd = getpwuid(fileStat.st_uid);
    printf(" %s ", pwd->pw_name); //username
    
    grp = getgrgid(fileStat.st_gid);
    printf(" %s ", grp->gr_name);//group
    
    printf(" %lld ",fileStat.st_size); //File Size

    char buff[20];
    struct tm * timeinfo;
    
    timeinfo = localtime (&(fileStat.st_mtime));
    strftime(buff, 20, "%b %d %H:%M", timeinfo);
    printf(" %s ",buff);
    
    timeinfo = localtime (&(fileStat.st_atime));
    strftime(buff, 20, "%b %d %H:%M", timeinfo);
    printf(" %s ",buff);

    
    //printf(" %s ", ctime(&fileStat.st_mtime)); //Last modified time
    //printf(" %s ", ctime(&fileStat.st_atime));//Last access time
    
    // -rw-r--r--@  1 juantepedino  staff  416420 Feb 19 13:01 Estructura y Salida ELS.pdf
    
    return 0;
}