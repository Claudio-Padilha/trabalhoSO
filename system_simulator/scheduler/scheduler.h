#ifndef  SCHEDULER_H
#define  SCHEDULER_H

    #include <time.h>
    #include "../memory/memory.h"
    #include "../queue/queue.h"
    #include "../disk/disk.h"
    #include "../timer/timer.h"
    #include "../swapper/swapper.h"
    #include "../shipper/shipper.h"

    typedef struct fcfsArgs 
    {
        queue * entry;
        queue * ready;
        memory * mem;
        disk * d;
        timer * t;  
    } fcfsArgs;

    typedef struct rrArgs 
    {
        queue * ready;
        memory * mem;
        disk * d;
        timer * t;
    } rrArgs;

    // This is used as a thread by FCFS scheduler. This waits for the timer to signal and move a process from entry queue to rady queue
    void * waitForTimer (void * param);

    // schedulerFCFS : FIFO politics
    // moves processes from entry queue to ready queue
    void * schedulerFCFS (void * param); 

    // schedulerRR : Round Robin algorithm
    // moves processes from ready queue to dispatcher
    void * schedulerRR (void * param);
#endif