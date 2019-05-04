#include <fila.h>

process * removeFirst (queue * q)
{
    if (q->first != NULL)
    {
        process * ret = q->first;            // gets first process and adjust the queue
        q->first = ret->next;

        if (q->first == NULL)                // no more processes in queue
        {
            q->last = NULL;
        }

        return ret;
    }

    return NULL;                            // queue was empty
}

int insert (process * p, queue * q)
{
    if (q->last == NULL)
    {                                       // no process in queue, so p is the first
        q->first = p;
    }else if (q->first == q->last)
    {                                       // p will be next to first if there is only one elem in queue
        q->first->next = p;
    }else
    {
        q->last->next = p;                   
    }
    q->last = p;                             // puts p in the end of the queue
    p->next = NULL;

    return p->id;                           
}