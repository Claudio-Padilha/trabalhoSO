#include "shipper.h"

void * shipper (void * param)
{
    shipperArgs * args = (shipperArgs *) param;
    pthread_mutex_lock(&args->mem->lock);                       
    pthread_mutex_lock(&args->d->lock);
    pthread_mutex_lock(&args->ready->lock);

        process * p = copyFromMemory(args->pid, args->mem);                         // Tries to coppy the  process from memory. There is still a reference in memory

        if (p == NULL)                                                              // process not in memory
        {
            swappArgs * sw = malloc(sizeof(swappArgs));
            sw->d = args->d;                                                         // aquire arguments for swapper in a structure
            sw->mem = args->mem;
            sw->pid = args->pid;

            pthread_t swa;
            pthread_create(&swa, NULL, swapper, (void *) sw);                      // call swapper as a thread
            pthread_join(swa, NULL);                                               // Waits untill swapper brings process from disk to memory
            p = copyFromMemory(args->pid, args->mem);                         // Copies the  process from memory. There is still a reference in memory   
        }

        int cpuTime = workOnProcess(p, args->t->timeQuantum);                   // Consumes tq or burstLeft (whichever is smaller) of process burst time and returns it
        if (p->burstTime > 0)                                       
        {
            insertIntoQueue(p->id, p->burstTime, p->size, args->ready);             // Puts process bak in ready queue if it still has burstTime
        }

    pthread_mutex_unlock(&args->mem->lock);                       
    pthread_mutex_unlock(&args->d->lock);
    pthread_mutex_unlock(&args->ready->lock);

    timerArgs * tmArgs = (timerArgs *) malloc(sizeof(timerArgs));
    tmArgs->cpuUsage = cpuTime;
    tmArgs->t = args->t;

    pthread_t tm;
    pthread_create(&tm, NULL, resetTimer, (void *) tmArgs);                         // reset the timer

    return NULL;
}