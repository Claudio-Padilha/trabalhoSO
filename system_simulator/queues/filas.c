#include <memoria.h>

typedef struct queues 
{
    int * entry;            // entry queue 
    int * ready;            // ready queue 
}queues;

// add to entry queue and returns process id
// or return -1 if memory is not available
int addEntryQueue (queues f, memory mem)       
{
    // TODO
}

int addReadyQueue (queues f, memory mem) 
{
    // TODO
}

// echelonFCFS : FIFO politics.
// moves from entry queue to ready queue
int echelonFCFS () 
{
    // TODO
}