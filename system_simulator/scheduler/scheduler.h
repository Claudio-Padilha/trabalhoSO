#ifndef  SCHEDULER_H
#define  SCHEDULER_H

    #include <time.h>
    #include "../memory/memory.h"
    #include "../queue/queue.h"
    #include "../disk/disk.h"

    typedef struct fcfsArgs 
    {
        queue * entry;
        queue * ready;
        memory * mem;
    } fcfsArgs;

    typedef struct rrArgs 
    {
        queue * ready;
        memory * mem;
        disk * d;
        timer * t;
    } rrArgs;

    // schedulerFCFS : FIFO politics
    // moves processes from entry queue to ready queue
    void * schedulerFCFS (void * param); 

    // schedulerRR : Round Robin algorithm
    // moves processes from ready queue to dispatcher
    void * schedulerRR (void * param);
#endif