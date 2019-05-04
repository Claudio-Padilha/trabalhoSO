#include <cpu.h>

void * workOnProcess (cpu c, process * p)
{
    pthread_mutex_lock(&memoryLock);                                // aquire memory lock because it will work on a process in memory
        p->burstTime -= c.timeQuantum;
    pthread_mutex_unlock(&memoryLock);
}