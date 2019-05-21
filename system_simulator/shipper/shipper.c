#include "shipper.h"

void * shipper (void * param)
{
    shipperArgs * args = (shipperArgs *) param;
    pthread_mutex_lock(&args->mem->lock);
        process * p = getFromMemory(args->pid, args->mem);                     // try to get process from memory
    pthread_mutex_unlock(&args->mem->lock);
    
    if (p == NULL)                                                              // process not in memory
    {
        swappArgs sw;
        sw.d = args->d;                                                         // aquire arguments for swapper in a structure
        sw.mem = args->mem;
        sw.pid = args->pid;

        pthread_t swa;
        pthread_create(&swa, NULL, swapper, (void *) &sw);                      // call swapper as a thread
        pthread_join(swa, NULL);
        pthread_mutex_lock(&args->mem->lock);
            p = getFromMemory(args->pid, args->mem);                           // gets the  process from memory
        pthread_mutex_unlock(&args->mem->lock);
    }

    pthread_mutex_lock(&args->t->lock);
        //resetTimer(p, args->t);                                                 // execute the process and reset timer

        //TODO
    pthread_mutex_unlock(&args->t->lock);
}