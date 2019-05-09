#ifndef CREATOR_H
#define CREATOR_H

    #include <unistd.h>
    #include <pthread.h>
    #include <queue.h>
    #include <time.h>

    // receives the list of processes oredered by arrival time (creation time)
    void * startCreator (process * ps, entryQueue * entry, int n, timer * t);

#endif