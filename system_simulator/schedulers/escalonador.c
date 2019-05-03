#include <escalonador.h>
#include <fila.h>
#include <memoria.h>

void * schedulerFCFS (queue entry, queue ready, memory mem) 
{   
    pthread_mutex_lock(&entryLock);                                          // aquire entry queue lock
    pthread_mutex_lock(&memoryLock);                 /**** SHOULD IT AQUIRE MEMORY LOCK TOO? (it reads from memory - memory.used parameter is variable) *****/
        if (entry.first == NULL)
        {
            return NULL;                                                    // queue is empty
        }
        else if (entry.first->size <= mem.size - mem.used)                  // verifies if there is enough space in memory
        {
            printf("Escalonador FCFS de longo prazo escolheu o processo %d", entry.first->id);

            process * p = removeFirst(entry);                               // removes and gets the first process from entry queue

            insert(p, ready);                                               // inserts the process into ready queue

            printf("Escalonador FCFS de longo prazo retirou o processo %d da fila de entrada, colocando-o na fila de prontos", p->id);
        }else 
        {
            printf("Escalonador FCFS de longo prazo não retirou o processo %d da fila de entrada porque não há espaço na memória", entry.first->id);
        }
    pthread_mutex_unlock(&entryLock);                                        // releases entry queue lock
    pthread_mutex_unlock(&memoryLock);
}


void * schedulerRR (process p, memory mem) 
{
    // TODO
}