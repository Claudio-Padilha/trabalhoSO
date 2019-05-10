#ifndef SHIPPER_H
#define SHIPPER_H

    #include <memory.h>
    #include <swapper.h>
    #include <time.h>

    // if a process is in memory, shipper sends it to CPU and reset timer. 
    // if not, it calls the swapper to bring the process from memory and execute it then.
    void * shipp (int pid, memory * mem, disk * d, timer * t);

#endif