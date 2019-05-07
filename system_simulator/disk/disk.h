#ifndef  DISK_H
#define  DISK_H

    #include <pthread.h>
    #include <stdlib.h>
    #include <process.h>

    // this is the disk structure
    typedef struct disk
    {
        // the disk is represented by a list. This points to the first process of the list. Each process points to the next. Has "infinite" space.
        process * list;
        // disk mutex
        pthread_mutex_t lock; 
    } disk;

    // creates a new disk. Returns null if something went wrong. It has to reiceive a ordered list of processes (by arrivalTime atribute)
    disk * newDisk(process * ps);

#endif