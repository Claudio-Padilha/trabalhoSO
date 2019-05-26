#ifndef SWAPPER_H
#define SWAPPER_H

#include <pthread.h>
#include <stdio.h>
#include "../disc/disc.h"
#include "../memory/memory.h"

// swapperArgs structure is used to pass arguments to swapper thread.
typedef struct swapperArgs
{
    disc * d;
    memory * m;

    // Process id
    int pid;
    
}swapperArgs;

// Returns the biggest interval on memory. Used for adjustments porpouse.
int getBiggestInterval (memory * mem);

// Gets a process copy from disc.
process * copyFromDisc (int pid, disc * d);

// Removes first process from memory and returns it.
process * firstFromMemory (memory * m);

// Brings a process to memory
int insertIntoMemory (process * p, memory * mem);

// Creates swapper thread
void * swapper (void * param);

#endif