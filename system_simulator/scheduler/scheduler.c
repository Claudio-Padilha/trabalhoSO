#include "scheduler.h"

void * waitForTimer (void * param)
{
    fcfsArgs * args =  (fcfsArgs *) param;
    while (1)                                               
    {
        pthread_cond_wait(&args->t->cond, &args->t->lock);      // Waits for timer signal
        pthread_mutex_lock(&args->entry->lock);
        if (args->entry->first != NULL)                         // If entry queue is not empty, moves a process from entry queue to ready queue
        {
            swappArgs * sargs;
            sargs->d = args->d;
            sargs->mem = args->mem;
            sargs->pid = args->entry->first;
            int pid = args->entry->first->pid;
            int burst = args->entry->first->burst;
            int size = args->entry->first->size;
            removeFromQueue (args->entry);                          // removes process from entry queue
            pthread_mutex_unlock(&args->entry->lock);

            pthread_t swap;
            pthread_create(&swapper, NULL, swapper, sargs);         // Calls swapper and put the process removed from entry queue in memory
            int check = pthread_join(swap, NULL);

            if (check == 0)                                         // Join with swapper was successful
            {
                pthread_mutex_lock(&args->ready->lock);
                insertIntoQueue(pid, burst, size, args->ready);     // Puts the process in ready queue
                pthread_mutex_unlock(&args->ready->lock); 
            }else{
                printf("Error with join between swapper and FCFS scheduler!");
            }
        }else{                                                      // Entry queue is empty
            pthread_mutex_unlock(&args->entry->lock);
        } 
    }  
}

void * schedulerFCFS (void * param) 
{ 
    fcfsArgs * args =  (fcfsArgs *) param; 
    pthread_t waitTimer;

    pthread_create(&waitTimer, NULL, waitForTimer, (void *) args);                  // Creates thread that will wait for timer signal. 
                                                                                    // We do not join because we need the above loop to run concurrently

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
            
            
            pthread_t swap;
            pthread_create(&swapper, NULL, swapper, sargs);         // Calls swapper and put the process removed from entry queue in memory
            int check = pthread_join(swap, NULL);

            if (check == 0)                                         // Join with swapper was successful
            {
                pthread_mutex_lock(&args->ready->lock);
                insertIntoQueue(pid, burst, size, args->ready);     // Puts the process in ready queue
                pthread_mutex_unlock(&args->ready->lock); 
            }else{
                printf("Error with join between swapper and FCFS scheduler!");
            }

            pthread_mutex_lock(&args->ready->lock);
            insertIntoQueue(pid, burst, size, args->ready);
            pthread_mutex_unlock(&args->ready->lock);   
        }
    }
}


void * schedulerRR (void * param) 
{
    rrArgs * args =  (rrArgs *) param;

    // TODO
}