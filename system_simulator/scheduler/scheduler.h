#ifndef  SCHEDULER_H
#define  SCHEDULER_H

#include "memory.h"
#include "queue.h"
#include "disk.h"
#include <time.h>

    // schedulerFCFS : FIFO politics
    // moves processes from entry queue to ready queue
    void * schedulerFCFS (Queue * entry, Queue * ready, memory * mem); 

    // schedulerRR : Round Robin algorithm
    // moves processes from ready queue to dispatcher
    void * schedulerRR (Queue * ready, memory * mem, disk * d, timer * t);
#endif
