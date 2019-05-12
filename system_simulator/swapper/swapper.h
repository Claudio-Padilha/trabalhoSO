#ifndef SWAPPER_H
#define SWAPPER_H

    #include "../disk/disk.h"
    #include "../memory/memory.h"
    #include "../process/process.h"

    typedef struct swappArgs
    {
        int pid;
        disk * d;
        memory * mem;
    }swappArgs;
    

    // gets a process from disk
    process * getFromDisk (int pid, disk * d);

    // puts a process into disk
    int swapperIntoDisk (process * p, disk * d);

     // Uses first-fit algorithm to put a process into memory
    int swapperIntoMemory (process * p, disk * d, memory * mem); 

    // gets a process from disk and puts it into memory.
    void * swapper (void * param);

#endif