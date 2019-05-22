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
    unsigned int useTime = workOnProcess(args->p, args->t->timeQuantum);                  // updates process burst time and return the elapsed time

    sleep(useTime);
    args->t->currentTime += useTime;

    pthread_exit(NULL);
}