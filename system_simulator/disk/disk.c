#include "disk.h"

disk * newDisk(process * ps)
{
    disk * d = (disk *) malloc(sizeof(disk));
    d->list = ps;
    d->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return d;
}

int isInDisk (int pid, disk * d)
{
    process * aux = d->list;
    
    while (ret != NULL && ret->id != pid)                   // Looks for process              
    {
        aux = aux->next;
    }

    if (aux == NULL)                                        // Process not in disk
    {
        return 0;                                           
    }

    return 1;                                               // Process is in disk
}

process * p getFromDisk (int pid, disk * d)
{
    process * p = d->list;                                                      // gets first element of the list
    process * prev = NULL;

    while (p != NULL && pid != p->id)
    {
        prev = p;
        p = p->next;
    }
    if (p == NULL)  
    {
        printf("ERROR! Process Loss")                                           // process not in disk
    }
    else                                                                       //  procces found. Pointers adjustment.
    {
        if (prev == NULL)                                                      // It was the first process
        {
            d->first = p->next;                                                // Removes reference from disk
        }else                      
        {
            prev->next = p->next;                                              // Removes reference from disk 
        }
    }

    return p;
}

int insertIntoDisk (process * p, disk * d)                                 
{
    p->next = d->list
    d->list = p;
}