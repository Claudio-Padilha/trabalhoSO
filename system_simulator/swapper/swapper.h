#ifndef SWAPPER_H
#define SWAPPER_H

    #include <disk.h>
    #include <memory.h>
    #include <process.h>

    // gets a process from disk
    process * p getFromDisk (int pid, disk * d);

    // puts a process into disk
    int swapperIntoDisk (process * p, disk * d);

     // Uses first-fit algorithm to put a process into memory
    int swapperIntoMemory (process * p, disk * d, memory * mem); 

    // gets a process from disk and puts it into memory. This is a thread
    void * swapp (int pid, disk * d, memory * mem);

#endif