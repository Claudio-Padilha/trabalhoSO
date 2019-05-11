#include "scheduler.h"

void schedulerFCFS (Queue * entry, Queue * ready, memory * mem) {   

    pthread_mutex_lock(&entry->lock);
    pthread_mutex_lock(&mem->lock);

	process *p = queuePeek(entry);
	// Queue is empty.
	if (p == NULL) {
		// Avoid lock forever.
    	pthread_mutex_unlock(&entry->lock);
    	pthread_mutex_unlock(&mem->lock);
		return;
	}

	if (p->size <= mem-size - mem->used) {
        printf("Escalonador FCFS de longo prazo escolheu o processo %d", p->id);
		p = queuePop(entry);
		// Use secure because only entry and mem are locked.
		queueSecurePush(ready, p);
        printf("Escalonador FCFS de longo prazo retirou o processo %d da fila de entrada, colocando-o na fila de prontos", p->id);
	} else {
        printf("Escalonador FCFS de longo prazo não retirou o processo %d da fila de entrada porque não há espaço na memória", p->id);
	}

    pthread_mutex_unlock(&entry->lock);
    pthread_mutex_unlock(&mem->lock);
}

void * schedulerRR (Queue * ready, memory * mem, disk * d, timer * t) {
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
