#include "timer.h"

timer * newTimer(int tq)
{
    timer * t = (timer *) malloc(sizeof(timer));
    t->timeQuantum = tq;
    t->currentTime = 0;
    t->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    t->condTq = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    t->condBurst = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    return t;   
}

void * resetTimer (void * param)
{
    timerArgs * args = (timerArgs *) param;

    sleep(args->cpuUsage);
    args->currentTime += args->cpuUsage;
    if (args->cpuUsage < args->t->timeQuantum)                             // Process ended burst time
    {
        pthread_cond_broadcast(&args->t->condBurst);                       // Signals to FCFS
    }

    pthread_cond_broadcast(&args->t->condBurst);                            // Signals to Round Robin    

    return NULL;
}