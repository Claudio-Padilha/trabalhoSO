#include "timer.h"

timer * newTimer(int tq)
{
    timer * t = (tmier *) malloc(sizeof(timer));
    t->timeQuantum = tq;
    t->currentTime = 0;
    t->lastUpdate = 0;
    t->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return t;   
}

void * resetTimer (process * p, timer * t)
{
    unsigned int useTime = workOnProcess(p, t->timeQuantum);                  // updates process burst time and return the elapsed time

    sleep(useTime);
    t->currentTime += useTime;
}