#ifndef  CPU_H
#define  CPU_H

    #include <pthread.h>
    #include <memoria.h>
    #include <processo.h>

    typedef struct cpu
    {
        int timeQuantum;
    }cpu;

    // mutex for cpu
    pthread_mutex_t cpuLock = PTHREAD_MUTEX_INITIALIZER;

    // Gives the process its share of cpu usage
    void * workOnProcess (cpu c, process * p);
#endif