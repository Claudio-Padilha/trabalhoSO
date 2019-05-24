#include "scheduler.h"

void * waitForTimer (void * param)
{
    fcfsArgs * args =  (fcfsArgs *) param;
    while (1)                                               
    {
        pthread_cond_wait(&args->t->condBurst, &args->t->lock);      // Waits for timer signal
        pthread_mutex_lock(&args->entry->lock);
        if (args->entry->first != NULL)                         // If entry queue is not empty, moves a process from entry queue to ready queue
        {
            swappArgs * sargs = (swappArgs *) malloc(sizeof(swappArgs));
            sargs->d = args->d;
            sargs->mem = args->mem;
            sargs->pid = args->entry->first->pid;
            int pid = args->entry->first->pid;
            int burst = args->entry->first->burst;
            int size = args->entry->first->size;
            removeFromQueue (args->entry);                          // removes process from entry queue
            pthread_mutex_unlock(&args->entry->lock);

            pthread_t swap;
            pthread_create(&swap, NULL, swapper, (void *) sargs);         // Calls swapper and put the process removed from entry queue in memory
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
            pthread_mutex_unlock(&args->mem->lock);
            continue;
        }else if (args->mem->biggestInterval >= args->entry->first->size)           // queue is not empty and there is space in memory
        {
            swappArgs * sargs = (swappArgs *) malloc(sizeof(swappArgs));
            sargs->d = args->d;
            sargs->mem = args->mem;
            sargs->pid = args->entry->first->pid;                                        // Argumrnts for swapper
            int pid = args->entry->first->pid;
            int burst = args->entry->first->burst;
            int size = args->entry->first->size;
            
            removeFromQueue (args->entry);                                              // Removes process from entry queue               

            struct tm * currentTime;
            time_t segundos;
            time(&segundos);   
            currentTime = localtime(&segundos);
            printf("Time: %d:%d:%d - Escalonador FCFS de longo prazo escolheu e retirou o processo %d da fila de entrada.\n", 
            currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, pid);

            pthread_mutex_unlock(&args->entry->lock);
            pthread_mutex_unlock(&args->mem->lock);
            
            time(&segundos);   
            currentTime = localtime(&segundos);
            printf("Time: %d:%d:%d - Escalonador FCFS de longo prazo solicitou que o Swapper traga %d a memoria.\n", 
            currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, pid);
            

            pthread_t swap;
            pthread_create(&swap, NULL, swapper, (void *) sargs);         // Calls swapper and put the process removed from entry queue in memory
            int check = pthread_join(swap, NULL);                         // Waits untill swapper puts process in memory

            if (check == 0)                                         // Join with swapper was successful
            {
                pthread_mutex_lock(&args->ready->lock);
                insertIntoQueue(pid, burst, size, args->ready);     // Puts the process in ready queue
                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Escalonador FCFS de longo prazo colocou %d na fila de prontos.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, pid);
                pthread_mutex_unlock(&args->ready->lock); 
            }else{
                printf("Error with join between swapper and FCFS scheduler!");
            }
        }
    }
}

void * schedulerRR (void * param) 
{
    rrArgs * args =  (rrArgs *) param;
    while (1)
    {
        pthread_cond_wait(&args->t->condTq, &args->t->lock);      // Waits for timer signal
        pthread_mutex_lock(&args->ready->lock);
        if (args->ready->first == NULL)                           // Queue is empty. Do nothing
        {
            continue;
        }
        // Queue is not empty
        shipperArgs * sargs = (shipperArgs *) malloc(sizeof(shipperArgs));
        sargs->d = args->d;
        sargs->mem = args->mem;                                 // Argumrnts for shipper
        sargs->pid = args->ready->first->pid;
        sargs->t = args->t;
        
        removeFromQueue(args->ready);                            // Removes process from ready queue
        pthread_mutex_unlock(&args->ready->lock);

        pthread_t ship;
        pthread_create(&ship, NULL, shipper, (void *) sargs);   // Moves the process to shipper

        struct tm * currentTime;
        time_t segundos;
        time(&segundos);   
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Escalonador Round-Robin de CPU escolheu o processo %d, retirou-o da fila de prontos e o encaminhou ao Despachante.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, sargs->pid);
    }
    
}