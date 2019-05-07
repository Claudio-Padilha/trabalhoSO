#ifndef SWAPPER_H
#define SWAPPER_H

    #include <disk.h>
    #include <memory.h>
    #include <process.h>

     // Uses first-fit algorithm to put a process into memory
    int processIntoMemory (process * p, disk * d, memory * mem);

    // gets a process from disk and puts it into memory. This is a thread
    void * swapp (int pid, disk * d, memory * mem);

#endif