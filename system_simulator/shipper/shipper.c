#include "shipper.h"

void * shipper (void * param)
{
    shipperArgs * args = (shipperArgs *) param;
    pthread_mutex_lock(&args->mem->lock);
        process * p = lookForProcess(args->pid, args->mem);                                        // try to get process from memory
    pthread_mutex_unlock(&args->mem->lock);
    
    if (p == NULL)                                                                // process not in memory
    {
        swappArgs sw;
        sw.d = args->d;
        sw.mem = args->mem;
        sw.pid = args->pid;

        pthread_t swa;
        pthread_create(&swa, NULL, swapper, (void *) &sw);                                         // swapper aquire all necessary locks and brings the process to memory
        pthread_mutex_lock(&args->mem->lock);
            p = lookForProcess(args->pid, args->mem);                                             // gets the  process from memory
        pthread_mutex_unlock(&args->mem->lock);
    }

    pthread_mutex_lock(&args->t->lock);
        resetTimer(p, args->t);                                                        // execute the process and reset timer
    pthread_mutex_unlock(&args->t->lock);
}