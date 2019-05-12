#ifndef SHIPPER_H
#define SHIPPER_H

    #include <time.h>
    #include <pthread.h>
    #include "../memory/memory.h"
    #include "../swapper/swapper.h"
    #include "../process/process.h"
    #include "../timer/timer.h"

    typedef struct shipperArgs 
    {
        int pid;
        memory * mem;
        disk * d;
        timer * t;
    }shipperArgs;

    // if a process is in memory, shipper sends it to CPU and reset timer. 
    // if not, it calls the swapper to bring the process from memory and execute it then.
    void * shipper (void * param);

#endif