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
    struct timespec remainingSleep = {0, 0};

    sleepyTime.tv_sec = 0;
    sleepyTime.tv_nsec = 1837272638;


    int res = nanosleep(&sleepyTime, &remainingSleep);

    if (res == 0)
    {
        printf("Sleep successful\n");
    }
    else if (res == -1)
    {
        printf("sleep failed\n%ld %ld\n", remainingSleep.tv_sec, remainingSleep.tv_nsec);
    }
    else
    {
        printf("some sleep left\n");
    }
    printf("Goodbye\n");

    return 0;
}
