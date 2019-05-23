#include "queue.h"

queue * newQueue()
{
    queue * q = (queue *) malloc(sizeof(queue));
    q->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    q->first = NULL;
    q->last = NULL;

    return q;
}

int removeFromQueue (queue * q)
{
    if (q->first != NULL)
    {
        int ret = q->first->pid;                                // Gets first process pid and adjust the queue
        node * aux = q->first;
        q->first = q->first->next;
        free(aux);

        if (q->first == NULL)                                   // No more processes in queue
        {
            q->last = NULL;
        }

        return ret;
    }

    return -1;                                                  // Queue was empty
}

int insertIntoQueue (int pid, int burst, int size, queue * q)
{
    node * n = (node *) malloc(sizeof(node));
    if (n == NULL)
    {
        return -1;                                            // Couldn't alocate node
    }
    n->pid = pid;
    n->burst = burst;
    n->size = size;
    if (q->last == NULL)
    {     
        q->first = n;                                         // No process in queue, so p is the first
        q->last = n;
    }
    else if (q->first == q->last)
    {                                                        // Process will be next to first if there is only one elem in queue
        q->first->next = n;
    }else
    {
        q->last->next = n;                                  // Process will be next to last
    }
    q->last = n;                                            // Puts p in the end of the queue
    n->next = NULL;

    return n->pid;                           
}