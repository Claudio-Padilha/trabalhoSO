#ifndef  CPU_H
#define  CPU_H

    #include <process.h>

    // Gives the process its share of cpu usage. Returns the elapsed time working on process
    int workOnProcess (process * p, int tq);
#endif