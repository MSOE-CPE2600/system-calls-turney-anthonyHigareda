/*********************************************************
* CPE 2600-121
* Dr. Turney
* Fall 2025
* 
* Anthony Higareda
* Lab 9: System Calls
* Created: 03 November 2025
*
* pmod.c
* Part 2: 
* This program will modify its own priority by 
* reducing it by 10,
* Sleep for 1,837,272,638 nanoseconds,
* Print a goodbye message and exit
*
* Compile with:
* gcc -o pmod pmod.c -Wall
**********************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    pid_t pid = getpid();
    int priority = getpriority(PRIO_PROCESS, pid);
    int newPriority = nice(-10);

    printf("Orig: %d\nNew: %d\n", priority, newPriority);

    struct timespec sleepyTime;

    sleepyTime.tv_sec = 1;
    sleepyTime.tv_nsec = 837272638;


    nanosleep(&sleepyTime, NULL);
    printf("Goodbye\n");

    return 0;
}
