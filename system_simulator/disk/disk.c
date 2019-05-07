#include <disk.h>
#include <pthread.h>

disk * newDisk()
{
    disk * d = (disk *) malloc(sizeof(disk));
    d->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return d;
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
        if (prev == NULL)
        {
            d->first = p->next;
        }else                      
        {
            prev->next = p->next;
        }
    }

    return p;
}

int processIntoDisk (process * p, disk * d)                                 
{
    if (d->first == NULL)                                                      // disk is empty
    {
        d->first = p;
        d->last = p;
    }
    else
    {
        process * aux = d->first;
        process * prev = NULL;

        while (aux->id < p->id) 
        {
            if (aux->next == NULL)
            {
                break;
            }
            prev = aux;
            aux = aux->next;
        }

        if (aux == disk->fisrt)                                                 // process goes in the first position
        {
            p->next = disk->first;
            disk->first = p;
        }
        else if (aux->next == NULL && aux->id < p->id)                          // process goes in the last position
        {
            d->last->next = p;
            d->last = p;
        }
        else                                                                // process goes between two other processes
        {
            prev->next = p;
            p->next = aux;        
        }
    }
    
}