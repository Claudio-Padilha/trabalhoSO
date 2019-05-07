#include <disk.h>
#include <pthread.h>

disk * newDisk(process * ps)
{
    disk * d = (disk *) malloc(sizeof(disk));
    d->list = ps;
    d->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return d;
}