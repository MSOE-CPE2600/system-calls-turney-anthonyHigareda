/*********************************************************
* CPE 2600-121
* Dr. Turney
* Fall 2025
* 
* Anthony Higareda
* Lab 9: System Calls
* Created: 03 November 2025
*
* finfo.c
* Part 3: 
* This program will display file information about a file
* specified via the command line. Display the following information:
* Type of file
* Permissions set on the file
* Owner of the file
* File size (in BYTES)
* Date and time of last modification
* If there is an error at any point, print an error and exit
*
* Compile with:
* gcc -o finfo finfo.c -Wall
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>

void printFileType(mode_t mode);
void printFilePermissions(mode_t mode);

int main(int argc, char* argv[])
{

    struct stat info;
    char *filename = argv[1]; // must be specified on command line upon execution

    printf("%s", filename);

    if (stat(filename, &info) == 0)
    {
        printFileType(info.st_mode);
        printFilePermissions(info.st_mode);
        printf("Owner: %d\n", info.st_uid);
        printf("File size: %lld bytes\n", (long long)info.st_size);
        printf("Last modified: %s\n", ctime(&info.st_mtime));
    }
    else
    {
        perror("Could not read file.\n");
    }

    return 0;
}

void printFileType(mode_t mode)
{
    if (S_ISREG(mode))
    {
        printf("Regular file\n");
    }
    else if (S_ISDIR(mode))
    {
        printf("Directory\n");
    }
    else if (S_ISLNK(mode))
    {
        printf("Symbolic link\n");
    }
    else if (S_ISCHR(mode))
    {
        printf("Character special file\n");
    }
    else if (S_ISBLK(mode))
    {
        printf("Block special file\n");
    }
    else if (S_ISFIFO(mode))
    {
        printf("Pipe\n");
    }
    else if (S_ISSOCK(mode))
    {
        printf("Socket\n");
    }
    else
    {
        perror("Unknown file type!\n");
    }
}

void printFilePermissions(mode_t mode)
{
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "g" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}