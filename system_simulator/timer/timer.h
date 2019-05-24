#ifndef TIMER_H
#define TIMER_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <pthread.h>
    #include "../cpu/cpu.h"
    #include "../process/process.h"
    #include "../timer/timer.h"

    typedef struct timer
    {
        int timeQuantum;            // slice of max time of cpu usage per acess
        int numberProcesses;        // total number of processes

        int endedProcesses;           // total number of processes ended
        
        pthread_mutex_t lock;
        pthread_cond_t condTq;      // Condition variable used to signal the end of time quantum
        pthread_cond_t condBurst;   // Condition variable used to signal the end of a process burst
        pthread_cond_t condEnd;     // Condition variable used to signal the end of the simulation
    }timer;

    typedef struct timerArgs 
    {
        timer * t;
        int cpuUsage;               // Amount of CPU time used (It could be time quantum or the amount left of procces burst time left)
        int ended;                  // flag indicating if process ended burst
        int pid;                    // pid of process currently in CPU
    }timerArgs;

    // creates a new timer
    timer * newTimer(int tq, int numberProcesses);

    // resets the timer and wait until cpu is done working on process p 
    void * resetTimer (void * param);
#endif