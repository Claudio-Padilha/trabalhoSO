#include <disk.h>
#include <pthread.h>

disk * newDisk()
{
    disk * d = (disk *) malloc(sizeof(disk));
    d->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return d;
}