#include "scheduler.h"

void * waitForTimer (void * param)
{
    fcfsArgs * args =  (fcfsArgs *) param;
    while (1)
    {
        pthread_cond_wait(&args->t->cond, &args->t->lock);
        pthread_mutex_lock(&args->entry->lock);
        if (args->entry->first != NULL)
        {
            swappArgs * sargs;
            sargs->d = args->d;
            sargs->mem = args->mem;
            sargs->pid = args->entry->first;
            int pid = args->entry->first->pid;
            int burst = args->entry->first->burst;
            int size = args->entry->first->size;
            removeFromQueue (args->entry);
            pthread_mutex_unlock(&args->entry->lock);
            swapper(sargs);
            pthread_mutex_lock(&args->ready->lock);
            insertIntoQueue(pid, burst, size, args->ready);
            pthread_mutex_unlock(&args->ready->lock); 
        }else{
            pthread_mutex_unlock(&args->entry->lock);
        }
        
    }
    
}

void * schedulerFCFS (void * param) 
{ 
    fcfsArgs * args =  (fcfsArgs *) param; 
    pthread_t waitTimer;

    pthread_create(&waitTimer, NULL, waitForTimer, (void *) args);                  // Creates thread that will wait for timer signal. 
                                                                                    // We do not join because we need the above will to run concurrently

    while (1)                                                                       // This while will check if there is someone in entry line and space in memory      
    {
        pthread_mutex_lock(&args->entry->lock);
        pthread_mutex_lock(&args->mem->lock);
        if (args->entry->first == NULL)                                             // Entry queue is empty
        {
            pthread_mutex_unlock(&args->entry->lock);
            pthreadmutex_unlock(&args->mem->lock);
            continue;
        }else if (args->mem->biggestInterval >= args->entry->first->size)           // queue is not empty and there is space in memory
        {
            swappArgs * sargs;
            sargs->d = args->d;
            sargs->mem = args->mem;
            sargs->pid = args->entry->first;
            int pid = args->entry->first->pid;
            int burst = args->entry->first->burst;
            int size = args->entry->first->size;
            removeFromQueue (args->entry);
            pthread_mutex_unlock(&args->entry->lock);
            pthread_mutex_unlock(&args->mem->lock);
            swapper(sargs);

            pthread_mutex_lock(&args->ready->lock);
            insertIntoQueue(pid, burst, size, args->ready);
            pthread_mutex_unlock(&args->ready->lock);   
        }


    }
}


void * schedulerRR (void * param) 
{
    fcfsArgs * args =  (fcfsArgs *) param;

    // TODO
}