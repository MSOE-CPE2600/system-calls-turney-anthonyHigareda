/*********************************************************
* CPE 2600-121
* Dr. Turney
* Fall 2025
* 
* Anthony Higareda
* Lab 9: System Calls
* Created: 29 October 2025
*
* info.c
* Part 1: This program prints:
* the current time in nanoseconds
* the system's network name
* the operating system name
* the operating system release and version
* the system's hardware type
* the numbre of CPUs on the system
* the total amount of physical memory IN BYTES
* the total amount of free memory IN BYTES
*
* Compile with:
* gcc -o info info.c -Wall
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

#define BILLION 1000000000

void gettime();
void gethostinfo();
void getnumprocs();
void getmemoryinfo();

int main(int argc, char const *argv[])
{
    gettime();  
    gethostinfo();
    getnumprocs();
    getmemoryinfo();
    return 0;
}

void gettime()
{
    // timespec struct that will contain time information
    struct timespec nanoTime;

    // clock_gettime() returns 0 if it was successful
    // Gets the current time from CLOCK_REALTIME and stores
    // the time in the timespec struct passed in
    if (!clock_gettime(CLOCK_REALTIME, &nanoTime))
    {
        // Prints the current time in nanoseconds
        // Number of seconds * 1 billion, plus the number of nanoseconds
        printf("Current time in nanoseconds: %lf\n", 
            ((double)nanoTime.tv_sec * BILLION) + nanoTime.tv_nsec);
    }
}

void gethostinfo()
{
    // utsname struct that will contain the system information
    struct utsname sysInfo;

    // uname() returns 0 if it was successful
    // Stores all system information in the 
    // utsname struct passed in
    if (!uname(&sysInfo))
    {
        // Prints all pertinent system information
        printf("System's network name: %s\n", sysInfo.nodename);
        printf("System's operating system name: %s\n", sysInfo.sysname);
        printf("Operating system's release date and version: %s > %s\n", 
            sysInfo.release, sysInfo.version);
        printf("System's hardware type: %s\n", sysInfo.machine);
    }
}

void getnumprocs()
{
    int numProcessors = get_nprocs();
    printf("Number of processors: %d\n", numProcessors);
}

void getmemoryinfo()
{
    long int pagesize = sysconf(_SC_PAGESIZE);
    long int totalNumPages = sysconf(_SC_PHYS_PAGES);
    long int totalAvailPages = sysconf(_SC_AVPHYS_PAGES);
    long int totalMemoryBytes;
    long int availMemoryBytes;

    if (pagesize != -1 && totalNumPages != -1)
    {
        totalMemoryBytes = totalNumPages * pagesize;
        printf("Total amount of physical memory: %ld bytes\n", totalMemoryBytes);
    }

    if (pagesize != -1 && totalAvailPages != -1)
    {
        availMemoryBytes = totalAvailPages * pagesize;
        printf("Total amount of available memory: %ld bytes\n", availMemoryBytes);
    }
}