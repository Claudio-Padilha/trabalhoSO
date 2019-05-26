#include "creator.h"

void * creator (void * param)
{
    creatorArgs * crArgs = (creatorArgs *) param;

    sleep(crArgs->p->creation);                                     // Waits until creation time.

    pthread_mutex_lock(&crArgs->entry->lock);                       // Aquires entry queue lock.

    // Alocates and initializes node
    node * n = malloc(sizeof(node));
    n->burst = crArgs->p->burst;                                           
    n->pid = crArgs->p->id;
    n->size = crArgs->p->size;
    n->next = NULL; 

    // Inserts process on entry queue.
    if (crArgs->entry->first == NULL)                               // Queue is empty.
    {
        // Puts node on queue
        crArgs->entry->first = n;
        crArgs->entry->last = n;
    }
    else if (crArgs->entry->first == crArgs->entry->last)           // There is only one element on queue
    {
        // Puts node on queue
        crArgs->entry->first->next = n;
        crArgs->entry->last = n;
    }
    else                                                            // More than one node on queue
    {
        // Puts node on queue
        crArgs->entry->last->next = n;
        crArgs->entry->last = n;
    }

    // Informs that process was put on entry queue
    struct tm * currentTime;
    time_t segundos;
    time(&segundos);   
    currentTime = localtime(&segundos);
    printf("Time: %d:%d:%d - Criador de processos criou o processo %d e o colocou na fila de entrada.\n", 
    currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, crArgs->p->id);

    pthread_mutex_unlock(&crArgs->entry->lock);                       // Releases entry queue lock.

    return NULL;
}