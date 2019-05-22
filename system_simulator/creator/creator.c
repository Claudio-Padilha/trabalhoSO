#include "creator.h"

void * creator (void * param)                                          // Receives an ordered list of all the processes.
{
    creatorArgs * args = (creatorArgs *) param;
    sleep(args->p->arrivalTime);
    pthread_mutex_lock(&args->entry->lock);
        insertIntoQueue(args->p->id, args->p->burstTime, args->entry);
    pthread_mutex_unlock(&args->entry->lock);
}