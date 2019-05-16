#include "scheduler.h"

void * schedulerFCFS (void * param) 
{ 
    fcfsArgs * args =  (fcfsArgs *) param; 
    pthread_mutex_lock(&args->entry->lock);                                          // aquire entry queue lock
    pthread_mutex_lock(&args->mem->lock);                 /**** SHOULD IT AQUIRE MEMORY LOCK TOO? (it reads from memory structure - memory.used parameter is variable) *****/
        if (args->entry->first == NULL)
        {
            return NULL;                                                    // queue is empty
            pthread_mutex_unlock(&args->entry->lock);                                        // releases entry queue lock
            pthread_mutex_unlock(&args->mem->lock);                                       // releases memory lock
        }
        else if (args->entry->first->size <= args->mem->size - args->mem->used)                  // verifies if there is enough space in memory
        {
            printf("Escalonador FCFS de longo prazo escolheu o processo %d", args->entry->first->id);

            process * p = removeFromQueue(args->entry);                               // removes and gets the first process from entry queue
            pthread_mutex_lock(&args->ready->lock);
                insertIntoQueue(p, args->ready);                                               // inserts the process into ready queue
            pthread_mutex_unlock(&args->ready->lock);

            printf("Escalonador FCFS de longo prazo retirou o processo %d da fila de entrada, colocando-o na fila de prontos", p->id);
        }
        else 
        {
            printf("Escalonador FCFS de longo prazo não retirou o processo %d da fila de entrada porque não há espaço na memória", entry->first->id);
        }
    pthread_mutex_unlock(&args->entry->lock);                                        // releases entry queue lock
    pthread_mutex_unlock(&args->mem->lock);                                          // releases memory lock
}


void * schedulerRR (void * param) 
{
    fcfsArgs * args =  (fcfsArgs *) param;

    // TODO
}