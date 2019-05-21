#include "scheduler.h"

void * schedulerFCFS (void * param) 
{ 
    fcfsArgs * args =  (fcfsArgs *) param; 
    pthread_mutex_lock(&args->entry->lock);                                          // aquire entry queue lock
    pthread_mutex_lock(&args->mem->lock);                 /**** SHOULD IT AQUIRE MEMORY LOCK TOO? (it reads from memory structure - memory.used parameter is variable) *****/
        while ()
    pthread_mutex_unlock(&args->entry->lock);                                        // releases entry queue lock
    pthread_mutex_unlock(&args->mem->lock);                                          // releases memory lock
}


void * schedulerRR (void * param) 
{
    fcfsArgs * args =  (fcfsArgs *) param;

    // TODO
}