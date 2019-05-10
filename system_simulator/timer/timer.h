#ifndef TIMER_H
#define TIMER_H

    #include <pthread.h>
    #include <cpu.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>

    typedef struct timer
    {
        int timeQuantum;            // slice of max time of cpu usage per acess
        int currentTime;            // total elapsed time
        
        pthread_mutex_t lock;
    }timer;

    // creates a new timer
    timer * newTimer(int tq);

    // resets the timer and wait until cpu is done working on process p 
    void * resetTimer (process * p, timer * t)
#endif