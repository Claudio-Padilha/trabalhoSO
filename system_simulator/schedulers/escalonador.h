#ifndef  ESCALONADOR_H
#define  ESCALONADOR_H

#include <memoria.h>
#include <fila.h>

    // schedulerFCFS : FIFO politics
    // moves from ready queue to dispatcher
    // return process id if successfull and -1 if not
    void * schedulerFCFS (queue entry, queue ready, memory mem); 

    // schedulerRR : Round 
    // moves from entry queue to ready queue
    // return process id if successfull and -1 if not
    void * schedulerRR (process p, memory mem);
#endif