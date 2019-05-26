#ifndef  DISC_H
#define  DISC_H

#include <pthread.h>
#include <stdlib.h>
#include "../process/process.h"

typedef struct disk
{

    int numberProcess;
    // storage is a list representing the disk. Each process has a pointer to next.
    process  ** storage;    

    // Disk's lock.
    pthread_mutex_t lock;      
}disc;

// Creates a new disc
disc * newDisc ();

#endif