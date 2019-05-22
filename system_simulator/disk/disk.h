#ifndef  DISK_H
#define  DISK_H

    #include <pthread.h>
    #include <stdlib.h>
    #include "../process/process.h"

    // this is the disk structure
    typedef struct disk
    {
        // the disk is represented by a list. This points to the first process of the list. Each process points to the next. Has "infinite" space.
        process * list;
        // disk mutex
        pthread_mutex_t lock; 
    } disk;

    // creates a new disk. Returns null if something went wrong. It has to reiceive a ordered list of processes (by arrivalTime atribute)
    disk * newDisk();

    // "Copies" a process from disk (sends a reference to memory)
    process * copyFromDisk (int pid, disk * d);

    // Puts a process in the first position in disk and returns process pid. Once the process is in disk, it doesn't get out. 
    int insertIntoDisk (process * p, disk * d);

#endif