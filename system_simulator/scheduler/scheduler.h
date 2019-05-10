#ifndef  SCHEDULER_H
#define  SCHEDULER_H

#include <memory.h>
#include <queue.h>
#include <disk.h>
#include <time.h>

    // schedulerFCFS : FIFO politics
    // moves processes from entry queue to ready queue
    void * schedulerFCFS (entryQueue * entry, readyQueue * ready, memory * mem); 

    // schedulerRR : Round Robin algorithm
    // moves processes from ready queue to dispatcher
    void * schedulerRR (readyQueue * ready, memory * mem, disk * d, timer * t);
#endif