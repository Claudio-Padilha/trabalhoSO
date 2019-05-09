#include <timer.h>

timer * newTimer(int tq)
{
    timer * t = (tmier *) malloc(sizeof(timer));
    t->timeQuantum = tq;
    t->currentTime = 0;
}

void * resetTimer (process * p, timer * t)
{
    unsigned int useTime = workOnProcess(p, t->timeQuantum);                  // updates process burst time and return the elapsed time

    sleep(useTime);
    t->currentTime += useTime;
}