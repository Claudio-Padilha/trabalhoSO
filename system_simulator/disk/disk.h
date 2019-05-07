#ifndef  DISK_H
#define  DISK_H

    #include <process.h>
    #include <pthread.h>

    // this is the disk structure
    typedef struct disk
    {
        // the disk is represented by a list. This points to the first process of the list. Each process points to the next. Has "infinite" space. Is ordered!
        process * list;
        // disk mutex
        pthread_mutex_t lock; 
    } disk;

    // creates a new disk. Returns null if something went wrong
    disk * newDisk();

    // gets a process from disk.
    process * p getFromDisk (int pid, disk * d);

     // puts process into disk. Keeps the disk ordered
    int processIntoDisk (process * p, disk * d);

#endif