#include "scheduler.h"

void * schedulerFCFS (void * param)
{
     fcfsArgs * fcArgs = (fcfsArgs *) param;

    while (1)                                                                  // While there is space on memory, it puts a processes on memory and on ready queue.
    {
        pthread_mutex_lock(&fcArgs->entry->lock);

        if (fcArgs->entry->first == NULL)                                       // Queue is empty.
        {
            pthread_mutex_unlock(&fcArgs->entry->lock);
        }
        else                                                                    // Entry queue is not empty. Ready lock aquired.
        {   
            pthread_mutex_lock(&fcArgs->m->lock);
            if (fcArgs->m->biggestInterval >= fcArgs->entry->first->size)       // There is space in memory
            {
                pthread_mutex_lock(&fcArgs->d->lock);

                swapperArgs * swArgs = malloc(sizeof(swapperArgs));
                swArgs->d = fcArgs->d;
                swArgs->m = fcArgs->m;                  
                swArgs->pid = fcArgs->entry->first->pid;

                // Alocates and initializes node to be insered in ready queue
                node * n = malloc(sizeof(node));
                n->burst = fcArgs->entry->first->burst;                                           
                n->pid = fcArgs->entry->first->pid;
                n->size = fcArgs->entry->first->size;
                n->next = NULL; 

                node * aux = fcArgs->entry->first;
                fcArgs->entry->first = fcArgs->entry->first->next;       // removes process from entry queue.
                free(aux);

                if (fcArgs->entry->first == NULL)                        // No more processes in queue.
                {
                    fcArgs->entry->last = NULL;
                }

                pthread_mutex_unlock(&fcArgs->entry->lock);
                pthread_mutex_unlock(&fcArgs->m->lock);
                pthread_mutex_unlock(&fcArgs->d->lock);
                struct tm * currentTime;
                time_t segundos;
                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Escalonador FCFS de longo prazo escolheu e retirou o processo %d da fila de entrada.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, n->pid);

                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Escalonador FCFS de longo prazo solicitou que o Swapper traga %d a memoria.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, n->pid);

                pthread_t sw;
                pthread_create(&sw, NULL, swapper, (void *) swArgs);            // Calls swapper as a thread.
                pthread_join(sw, NULL);                                         // Waits for swapper to bring the process to memory.

                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Swapper avisa o Escalonador FCFS de longo prazo que o processo %d esta na memoria.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, n->pid);

                pthread_mutex_lock(&fcArgs->ready->lock);

                // Inserts process on ready queue.
                if (fcArgs->ready->first == NULL)                               // Queue is empty.
                {
                    // Puts node on queue
                    fcArgs->ready->first = n;
                    fcArgs->ready->last = n;
                }
                else if (fcArgs->ready->first == fcArgs->ready->last)           // There is only one element on queue.
                {
                    // Puts node on queue
                    fcArgs->ready->first->next = n;
                    fcArgs->ready->last = n;
                }
                else                                                            // More than one node on queue.
                {
                    // Puts node on queue
                    fcArgs->ready->last->next = n;
                    fcArgs->ready->last = n;
                }

                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Escalonador FCFS de longo prazo colocou %d na fila de prontos.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, n->pid);


                pthread_mutex_unlock(&fcArgs->ready->lock);

            }
            else                                                                // There is not space on memory.
            {
                pthread_mutex_unlock(&fcArgs->entry->lock);
                pthread_mutex_unlock(&fcArgs->m->lock);
                break;
            }
        }
    }

    while (1)
    {
        pthread_mutex_lock(&fcArgs->t->lock);
        pthread_cond_wait(&fcArgs->t->condBurst, &fcArgs->t->lock);             // Waits for timer to signal.
        pthread_mutex_unlock(&fcArgs->t->lock);

        while (1) 
        {
            pthread_mutex_lock(&fcArgs->entry->lock);
            if (fcArgs->entry->first != NULL)                                   // Entry queue is not empty.
            {
                pthread_mutex_lock(&fcArgs->m->lock);
                pthread_mutex_lock(&fcArgs->d->lock);

                swapperArgs * swArgs = malloc(sizeof(swapperArgs));
                swArgs->d = fcArgs->d;
                swArgs->m = fcArgs->m;                  
                swArgs->pid = fcArgs->entry->first->pid;

                // Alocates and initializes node to be insered in ready queue
                node * n = malloc(sizeof(node));
                n->burst = fcArgs->entry->first->burst;                                           
                n->pid = fcArgs->entry->first->pid;
                n->size = fcArgs->entry->first->size;
                n->next = NULL; 

                node * aux = fcArgs->entry->first;
                fcArgs->entry->first = fcArgs->entry->first->next;       // removes process from entry queue.
                free(aux);

                // Pointer adjustments.
                if (fcArgs->entry->first == NULL)                        // No more processes in queue.
                {
                    fcArgs->entry->last = NULL;
                }

                pthread_mutex_unlock(&fcArgs->entry->lock);
                pthread_mutex_unlock(&fcArgs->m->lock);
                pthread_mutex_unlock(&fcArgs->d->lock);

                struct tm * currentTime;
                time_t segundos;
                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Escalonador FCFS de longo prazo escolheu e retirou o processo %d da fila de entrada.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, n->pid);
                
                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Escalonador FCFS de longo prazo solicitou que o Swapper traga %d a memoria.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, n->pid);

                pthread_t sw;
                pthread_create(&sw, NULL, swapper, (void *) swArgs);            // Calls swapper as a thread.
                pthread_join(sw, NULL); 

                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Swapper avisa o Escalonador FCFS de longo prazo que o processo %d esta na memoria.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, n->pid);
                
                pthread_mutex_lock(&fcArgs->ready->lock);

                // Inserts process on ready queue.
                if (fcArgs->ready->first == NULL)                               // Queue is empty.
                {
                    // Puts node on queue
                    fcArgs->ready->first = n;
                    fcArgs->ready->last = n;
                }
                else if (fcArgs->ready->first == fcArgs->ready->last)           // There is only one element on queue.
                {
                    // Puts node on queue
                    fcArgs->ready->first->next = n;
                    fcArgs->ready->last = n;
                }
                else                                                            // More than one node on queue.
                {
                    // Puts node on queue
                    fcArgs->ready->last->next = n;
                    fcArgs->ready->last = n;
                }

                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Escalonador FCFS de longo prazo colocou %d na fila de prontos.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, n->pid);

                pthread_mutex_unlock(&fcArgs->ready->lock);                                        // Waits for swapper to bring the process to memory.

                break;
            }
            else
            {
                pthread_mutex_unlock(&fcArgs->entry->lock);
            } 
        }
    }
    return NULL;
}

void * schedulerRR (void * param)
{
    rrArgs * args =  (rrArgs *) param;

    while (1)                                                       // wait for the first process to enter ready queue
    {
        pthread_mutex_lock(&args->ready->lock);
        if (args->ready->first != NULL)                             // Queue is not empty
        {   
            pthread_mutex_lock(&args->d->lock);
            pthread_mutex_lock(&args->m->lock);
            pthread_mutex_lock(&args->t->lock);
            shipperArgs * sargs = (shipperArgs *) malloc(sizeof(shipperArgs));
            sargs->tq = args->t->timeQuantum;
            sargs->d = args->d;
            sargs->m = args->m;                                 // Argumrnts for shipper
            sargs->pid = args->ready->first->pid;
            sargs->t = args->t;

            int tq = args->t->timeQuantum;

            pthread_mutex_unlock(&args->d->lock);
            pthread_mutex_unlock(&args->m->lock);
            pthread_mutex_unlock(&args->t->lock);

            node * aux = args->ready->first;
            aux->burst -= tq;
            args->ready->first = args->ready->first->next;       // removes process from ready queue.

            //Pointer adjustments.
            if (args->ready->first == NULL)                        // No more processes in queue.
            {
                args->ready->last = NULL;
            }else if (args->ready->first->next == NULL)           // Only one more process in queue.
            {
                args->ready->last = args->ready->first;
            }

            pthread_t ship;
            pthread_create(&ship, NULL, shipper, (void *) sargs);   // Moves the process to shipper

            struct tm * currentTime;
            time_t segundos;
            time(&segundos);   
            currentTime = localtime(&segundos);
            printf("Time: %d:%d:%d - Escalonador Round-Robin de CPU escolheu o processo %d, retirou-o da fila de prontos e o encaminhou ao Despachante.\n", 
            currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, sargs->pid); 

            if (aux->burst > 0)                                     // Puts process back on ready queue if it has burst time
            {
                // Inserts process on ready queue.
                if (args->ready->first == NULL)                               // Queue is empty.
                {
                    // Puts node on queue
                    args->ready->first = aux;
                    args->ready->last = aux;
                }
                else if (args->ready->first == args->ready->last)           // There is only one element on queue.
                {
                    // Puts node on queue
                    args->ready->first->next = aux;
                    args->ready->last = aux;
                }
                else                                                            // More than one node on queue.
                {
                    // Puts node on queue
                    args->ready->last->next = aux;
                    args->ready->last = aux;
                }
            }else 
            {
                free(aux);
            } 

            pthread_mutex_unlock(&args->ready->lock);
            break;  
        }else{
           pthread_mutex_unlock(&args->ready->lock); 
        }
    }

    while (1)
    {
        pthread_mutex_lock(&args->t->lock);
        pthread_cond_wait(&args->t->condTq, &args->t->lock);             // Waits for timer to signal.
        pthread_mutex_unlock(&args->t->lock);

        while (1)
        {
            pthread_mutex_lock(&args->ready->lock);
            if (args->ready->first != NULL)                             // Queue is not empty
            {   
                pthread_mutex_lock(&args->d->lock);
                pthread_mutex_lock(&args->m->lock);
                pthread_mutex_lock(&args->t->lock);
                shipperArgs * sargs = (shipperArgs *) malloc(sizeof(shipperArgs));
                sargs->tq = args->t->timeQuantum;
                sargs->d = args->d;
                sargs->m = args->m;                                 // Argumrnts for shipper
                sargs->pid = args->ready->first->pid;
                sargs->t = args->t;

                int tq = args->t->timeQuantum;

                pthread_mutex_unlock(&args->d->lock);
                pthread_mutex_unlock(&args->m->lock);
                pthread_mutex_unlock(&args->t->lock);

                node * aux = args->ready->first;
                aux->burst -= tq;
                args->ready->first = args->ready->first->next;       // removes process from ready queue.

                //Pointer adjustments.
                if (args->ready->first == NULL)                        // No more processes in queue.
                {
                    args->ready->last = NULL;
                }else if (args->ready->first->next == NULL)           // Only one more process in queue.
                {
                    args->ready->last = args->ready->first;
                }

                pthread_t ship;
                pthread_create(&ship, NULL, shipper, (void *) sargs);   // Moves the process to shippe
                
                 if (aux->burst > 0)                                     // Puts process back on ready queue if it has burst time
                {
                    // Inserts process on ready queue.
                    if (args->ready->first == NULL)                               // Queue is empty.
                    {
                        // Puts node on queue
                        args->ready->first = aux;
                        args->ready->last = aux;
                    }
                    else if (args->ready->first == args->ready->last)           // There is only one element on queue.
                    {
                        // Puts node on queue
                        args->ready->first->next = aux;
                        args->ready->last = aux;
                    }
                    else                                                            // More than one node on queue.
                    {
                        // Puts node on queue
                        args->ready->last->next = aux;
                        args->ready->last = aux;
                    }
                }else 
                {
                    free(aux);
                } 

                struct tm * currentTime;
                time_t segundos;
                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Escalonador Round-Robin de CPU escolheu o processo %d, retirou-o da fila de prontos e o encaminhou ao Despachante.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, sargs->pid);

                pthread_mutex_unlock(&args->ready->lock);    

                break;  
            }else{
            pthread_mutex_unlock(&args->ready->lock); 
            }
        }
        
    }
}