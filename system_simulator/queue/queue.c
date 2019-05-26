#include "queue.h"
#include "queue.h"

node * newNode (int pid, int burst, int size)
{
    node * ret = malloc(sizeof(node));
    ret->pid = pid;
    ret->burst = burst;
    ret->size = size;
    ret->next = NULL;

    return ret;
}

queue * newQueue () 
{
    queue * ret = malloc(sizeof(queue));
    ret->first = NULL;
    ret->last = NULL;
    ret->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return ret;
}