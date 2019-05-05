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

    while (p != NULL && pid != p->id)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        printf("ERROR! Process Loss")                                           // process not in disk
    }

    return p;
}