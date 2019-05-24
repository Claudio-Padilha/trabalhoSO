#include "creator.h"

void * creator (void * param)                                          // Receives an ordered list of all the processes.
{
    creatorArgs * args = (creatorArgs *) param;
    sleep(args->p->arrivalTime);
    pthread_mutex_lock(&args->entry->lock);

        insertIntoQueue(args->p->id, args->p->burstTime, args->p->size, args->entry);

        struct tm * currentTime;
        time_t segundos;
        time(&segundos);   
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Criador de processos criou o processo %d e o colocou na fila de entrada.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, args->p->id);
    pthread_mutex_unlock(&args->entry->lock);

    return NULL;
}