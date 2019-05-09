#ifndef TIMER_H
#define TIMER_H

    #include <pthread.h>
    #include <cpu.h>
    #include <stdlib.h>
    #include <unistd.h>

    typedef struct timer
    {
        int timeQuantum;            // slice of max time of cpu usage per acess
        int currentTime;           // total elapsed time
    }timer;

    timer * newTimer(int tq);
#endif