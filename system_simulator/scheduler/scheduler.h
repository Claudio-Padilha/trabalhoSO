#ifndef  SCHEDULER_H
#define  SCHEDULER_H
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include "../memory/memory.h"
#include "../queue/queue.h"
#include "../disc/disc.h"
#include "../timer/timer.h"
#include "../swapper/swapper.h"
#include "../shipper/shipper.h"

typedef struct fcfsArgs 
{
    queue * entry;
    queue * ready;
    memory * m;
    disc * d;
    timer * t;  
} fcfsArgs;

typedef struct rrArgs 
{
    queue * ready;
    memory * m;
    disc * d;
    timer * t;
} rrArgs;

// schedulerFCFS : FIFO politics
// moves processes from entry queue to ready queue
void * schedulerFCFS (void * param); 

// schedulerRR : Round Robin algorithm
// moves processes from ready queue to dispatcher
void * schedulerRR (void * param);
#endif