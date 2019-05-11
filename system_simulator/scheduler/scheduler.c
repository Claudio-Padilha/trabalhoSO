#include <scheduler.h>

void * schedulerFCFS (entryQueue * entry, readyQueue * ready, memory * mem) 
{   
    pthread_mutex_lock(&entry->lock);                                          // aquire entry queue lock
    pthread_mutex_lock(&mem->lock);                 /**** SHOULD IT AQUIRE MEMORY LOCK TOO? (it reads from memory structure - memory.used parameter is variable) *****/
        if (entry->first == NULL)
        {
            return NULL;                                                    // queue is empty
        }
        else if (entry->first->size <= mem->size - mem->used)                  // verifies if there is enough space in memory
        {
            printf("Escalonador FCFS de longo prazo escolheu o processo %d", entry->first->id);

            process * p = removeFromQueue(entry);                               // removes and gets the first process from entry queue
            insertIntoQueue(p, ready);                                               // inserts the process into ready queue

            printf("Escalonador FCFS de longo prazo retirou o processo %d da fila de entrada, colocando-o na fila de prontos", p->id);
        }else 
        {
            printf("Escalonador FCFS de longo prazo não retirou o processo %d da fila de entrada porque não há espaço na memória", entry->first->id);
        }
    pthread_mutex_unlock(&entry->lock);                                        // releases entry queue lock
    pthread_mutex_unlock(&mem->lock);                                       // releases memory lock
}


void * schedulerRR (readyQueue * ready, memory * mem, disk * d, timer * t) 
{
    if (ready->last == NULL)                            // queue is empty
    {
        return NULL;
    }

    pit_t pid = fork();

    if (pid == 0)                                       // child porcess;
    {   
        pthread_mutex_lock(&ready->lock);
            process * p = removeFromQueue(ready);
        pthread_mutex_unlock(&ready->lock);
        shipp(p->id, mem,d ,t);                         // ship aquires all the locks it needs
    }
    else                                                // parent process
    {
        wait();
    }

}