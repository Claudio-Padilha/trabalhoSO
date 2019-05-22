#ifndef TIMER_H
#define TIMER_H

    #include <stdlib.h>
    #include <unistd.h>
    #include <pthread.h>
    #include "../cpu/cpu.h"

    typedef struct timer
    {
        int timeQuantum;            // slice of max time of cpu usage per acess
        int currentTime;            // total elapsed time
        
        pthread_mutex_t lock;
        pthread_cond_t cond;
    }timer;

    typedef struct timerArgs 
    {
        process * p;
        timer * t;
    }timerArgs;

    // creates a new timer
    timer * newTimer(int tq);

    // resets the timer and wait until cpu is done working on process p 
    void * resetTimer (void * param);
#endif