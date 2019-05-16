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

    // gets a process from disk and puts it into memory.
    void * swapper (void * param);

#endif