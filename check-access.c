//
//  moveDirTree.c
//  CPMA
//
//  Created by Juan Tepedino on 20/2/17.
//  Copyright © 2017 Juan Ortiz and Andrés Buelva. All rights reserved.
//

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <time.h>
#include <sys/stat.h>

#include <pwd.h>
#include <grp.h>


/*
 struct stat {
 dev_t     st_dev;      ID of device containing file
mode_t    st_mode;     protection
nlink_t   st_nlink;    number of hard links
uid_t     st_uid;     user ID of owner
gid_t     st_gid;      group ID of owner
off_t     st_size;     total size, in bytes
time_t    st_atime;    time of last access
time_t    st_mtime;    time of last modification
};
 
mode  | links |  owner  | group |  bytes | last modified | path.*/

int main (int argc, char* argv[]) {
    char* path = argv[1];
    int rval;

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

    
    char cwd[100000];
    getcwd(cwd, sizeof(cwd));
    //printf("\n%s", cwd);
    
    struct stat fileStat;
    if(stat(cwd,&fileStat) < 0)
        return 1;
    
    printf("Information for %s\n",argv[1]);
    printf("---------------------------\n");
    printf("File Size: \t\t%lld bytes\n",fileStat.st_size);
    printf("Number of Links: \t%d\n",fileStat.st_nlink);
    
    printf("File Permissions: \t");
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
    
    printf("\nThe file %s a symbolic link", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
    
    printf("\nLast modified time: %s", ctime(&fileStat.st_mtime));
    printf("Last access time: %s", ctime(&fileStat.st_atime));
    
    
    struct group *grp;
    struct passwd *pwd;
    
    grp = getgrgid(fileStat.st_gid);
    printf("group: %s\n", grp->gr_name);
    
    pwd = getpwuid(fileStat.st_uid);
    printf("username: %s\n", pwd->pw_name);
    
    
    
    char buff[20];
    struct tm * timeinfo;
    
    timeinfo = localtime (&(fileStat.st_mtime));
    strftime(buff, 20, "%b %d %H:%M", timeinfo);
    printf("%s",buff);
    
    return 0;
}