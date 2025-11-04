/*********************************************************
* CPE 2600-121
* Dr. Turney
* Fall 2025
* 
* Anthony Higareda
* Lab 9: System Calls
* Created: 30 October 2025
*
* pinfo.c
* Part 2: 
* This program will print the following for the current process:
* Process priority
* Scheduling method (as a string)
* If the process id does not exists, print an error and exit
* If a process id is not specified, print the info
* for the current executing process
*
* Compile with:
* gcc -o pinfo pinfo.c -Wall
**********************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    
    pid_t pid = getpid();
    int priority = getpriority(PRIO_PROCESS, pid);
    int schedule = sched_getscheduler(pid); 
    // Through my research, I have found that there are 4 standard scheduling policies
    // indicated by the values of these symbolic constants:
    // SCHED_FIFO
    // SCHED_RR
    // SCHED_SPORADIC
    // SCHED_OTHER
    // sched_getscheduler returns an int, which is supposed to correspond to one of these
    // policies, but I have been unable to determine what the values of these
    // constants are, so I cannot print out the string of what the constant actually is
    // pubs.opengroup.org/onlinepubs/9799919799/basedefs/sched.h.html 

    printf("Process ID: %d\nPriority: %d\nScheduling Method: %d\n", pid, priority, schedule);

    return 0;
}