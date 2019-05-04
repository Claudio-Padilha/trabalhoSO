#ifndef  ESCALONADOR_H
#define  ESCALONADOR_H

#include <memoria.h>
#include <fila.h>

    // schedulerFCFS : FIFO politics
    // moves processes from entry queue to ready queue
    void * schedulerFCFS (queue * entry, queue * ready, memory * mem); 

    // schedulerRR : Round Robin algorithm
    // moves processes from ready queue to dispatcher
    void * schedulerRR (process * p, memory * mem);
#endif