#ifndef SWAPPER_H
#define SWAPPER_H

    #include <disk.h>
    #include <memory.h>
    #include <process.h>

    // gets a process from disk and puts it into memory. This is a thread
    void * swapp (int pid, disk * d, memory * mem);

#endif