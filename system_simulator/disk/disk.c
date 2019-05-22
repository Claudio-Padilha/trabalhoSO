#include "disk.h"

disk * newDisk()
{
    disk * d = (disk *) malloc(sizeof(disk));
    d->list = NULL;
    d->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return d;
}

process * copyFromDisk (int pid, disk * d)
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
        printf("ERROR! Process Loss");                                           // process not in disk
    }
    

    return p;
}

int insertIntoDisk (process * p, disk * d)                                 
{
    p->next = d->list;
    d->list = p;
}