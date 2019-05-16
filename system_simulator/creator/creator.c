#include "creator.h"

void * startCreator (void * param)                                          // Receives an ordered list of all the processes.
{
    creatorArgs * args = (creatorArgs *) param;
    int prevArrival;                                                        // Previous arrival time
    sleep(args->ps->arrivalTime);

    pthread_mutex_lock(&args->entry->lock);
        prevArrival = args->ps->arrivalTime;
        insertIntoQueue(args->ps->id, args->ps->burstTime, entry);          
        args->ps = args->ps->next;                                          // Removes Process reference from creator
    pthread_mutex_unlock(&args->entry->lock);

    for (int i = 1; i<n; i++)                                               // Goes through all processes and creates them at instant "arrivalTime"
    {
        sleep(ps->arrivalTime - prevArrival);                               // Wait until next moment it has to create another process
        
        pthread_mutex_lock(&args->entry->lock);
            prevArrival = args->ps->arrivalTime;
            insertIntoQueue(args->ps->id, args->ps->burstTime, entry);
            arg->ps = args->ps->next;
        pthread_mutex_unlock(&args->entry->lock);

    }
}