#ifndef  CPU_H
#define  CPU_H

    #include <pthread.h>
    #include <memoria.h>
    #include <processo.h>

    typedef struct cpu
    {
        int timeQuantum;
        pthread_mutex_t lock;
    }cpu;

    // Gives the process its share of cpu usage
    void * workOnProcess (cpu * c, process * p, memory * mem);
#endif