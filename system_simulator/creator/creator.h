#ifndef CREATOR_H
#define CREATOR_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "../process/process.h"
#include "../queue/queue.h"
#include "../disc/disc.h"

// Structure used to pass arguments to the creator's thread.
typedef struct creatorArgs
{   
    // Process to be created.
    process * p; 
    // Entry queue
    queue * entry;
}creatorArgs;

// Creates the creator thread, putting the processe on entry queue on the proper time.
void * creator (void * param);

#endif