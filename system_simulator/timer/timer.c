#include "timer.h"

timer * newTimer(int tq, int burstTotal)
{
    timer * t = (timer *) malloc(sizeof(timer));
    t->timeQuantum = tq;
    t->currentTime = 0;
    t->burstTotal = burstTotal;
    t->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    t->condTq = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    t->condBurst = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    t->condEnd = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    return t;   
}

void * resetTimer (void * param)
{
    timerArgs * args = (timerArgs *) param;

    sleep(args->cpuUsage);
    args->t->currentTime += args->cpuUsage;

    if (args->cpuUsage < args->t->timeQuantum)                             // Process ended burst time
    {
        pthread_cond_broadcast(&args->t->condBurst);                       // Signals to FCFS
    }

    pthread_cond_broadcast(&args->t->condBurst);                            // Signals to Round Robin 

    if (args->t->burstTotal == args->t->currentTime)                        // All processes ended
    {
        pthread_cond_broadcast(&args->t->condEnd);                        // Signals the end of the execution to simulaotr
    }   

    return NULL;
}