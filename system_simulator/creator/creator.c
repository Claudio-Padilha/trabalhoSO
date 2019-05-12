#include "creator.h"

void * startCreator (void * param)                          // ps is a ordered list of all the processes. comes from disk.
{
    creatorArgs * args = (creatorArgs *) param;
    process * prev;
    sleep(args->ps->arrivalTime);

    pthread_mutex_lock(&args->t->lock);
        args->t->currentTime += args->ps->arrivalTime;                                  // update current time
    pthread_mutex_unlock(&t->lock);

    pthread_mutex_lock(&args->entry->lock);
        prev = args->ps;
        insertIntoQueue(args->ps, entry);
        args->ps = args->ps->next;
    pthread_mutex_unlock(&entry->lock);

    for (int i = 1; i<n; i++)
    {
        sleep(ps->arrivalTime - prev->arrivalTime);                         // wait until next moment it has to create another process
        
        pthread_mutex_lock(&args->entry->lock);
            prev = args->ps;
            insertIntoQueue(args->ps, args->entry);
            arg->ps = args->ps->next;
        pthread_mutex_unlock(&args->entry->lock);

    }
}