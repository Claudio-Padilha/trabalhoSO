#ifndef CREATOR_H
#define CREATOR_H

    #include <unistd.h>
    #include <pthread.h>
    #include <time.h>
    #include "../queue/queue.h"
    #include "../process/process.h"

    typedef struct creatorArgs
    {
        process * ps;                                        // ordered list of processes
        queue * entry;
        int n;                                               // number of processes
    } creatorArgs;

    // receives the list of processes oredered by arrival time (creation time)
    void * startCreator (void * param);

#endif