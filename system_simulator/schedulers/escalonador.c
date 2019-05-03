#include <escalonador.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;                       // *** DOUBT **** maybe should pass this through functions, to give it a bigger scope

void * schedulerFCFS (queue entry, queue ready, memory mem) 
{   
    pthread_mutex_lock(&lock);                                          // aquire lock

        if (entry.first == NULL)
        {
            return NULL;                                                // queue is empty
        }
        else if (entry.first->size <= mem.used)                         // verifies if there is enough space in memory
        {
            printf("Escalonador FCFS de longo prazo escolheu o processo %d", entry.first->id);

            process * p = removeFirst(entry);                           // removes and gets the first process from entry queue

            insert(p, ready);                                           // inserts the process into ready queue

            printf("Escalonador FCFS de longo prazo retirou o processo %d da fila de entrada, colocando-o na fila de prontos", p->id);
        }else 
        {
            printf("Escalonador FCFS de longo prazo não retirou o processo %d da fila de entrada porque não há espaço na memória", entry.first->id);
        }
    pthread_mutex_unlock(&lock);                                        // releases lock
}


void * schedulerRR (process p, memory mem) 
{
    // TODO
}