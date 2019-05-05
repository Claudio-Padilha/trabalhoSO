#ifndef  CPU_H
#define  CPU_H

    #include <pthread.h>
    #include <memory.h>
    #include <process.h>

    typedef struct cpu
    {
        int timeQuantum;
        pthread_mutex_t lock;
    }cpu;

    // Gives the process its share of cpu usage
    int workOnProcess (cpu * c, process * p, memory * mem);
#endif