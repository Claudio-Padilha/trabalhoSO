#ifndef CREATOR_H
#define CREATOR_H

    #include <unistd.h>
    #include <pthread.h>
    #include <time.h>
    #include "../queue/queue.h"
    #include "../process/process.h"

    typedef struct creatorArgs
    {
        process * p;                                         // The process to be created
        queue * entry;
    } creatorArgs;

    // Receives a process and puts it in entry queue on the proper time
    void * creator (void * param);

#endif