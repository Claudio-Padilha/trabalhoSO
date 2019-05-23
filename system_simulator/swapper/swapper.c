#include "swapper.h"

void * swapper (void * param)
{
    swappArgs * args = (swappArgs *) param;
    pthread_mutex_lock(&args->d->lock);                                       // aquire disk lock
    pthread_mutex_lock(&args->mem->lock);                                     // aquire memory lock
        process * p = copyFromDisk(args->pid, args->d);                         // gets a process from disk
        insertIntoMemory (p, args->mem, args->d);                              // puts the process into memory    
    pthread_mutex_unlock(&args->mem->lock);                                   // releases memory lock
    pthread_mutex_unlock(&args->d->lock);                                     // releases disk lock

    return p;         
}