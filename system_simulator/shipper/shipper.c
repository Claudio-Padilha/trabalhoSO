#include <shipper.h>

void * shipp (int pid, memory * mem, disk * d, timer * t)
{
    process * p = lookForProcess(pid, mem);                                        // try to get process from memory
    
    if (p == NULL)                                                                // process not in memory
    {
        swapp(pid, d, mem);                                                       // swapps aquire all necessary locks and brings the process to memory
        p = lookForProcess(pid, mem);                                             // gets the  process from memory
    }

    pthread_mutex_lock(&t->lock);
        resetTimer(p, t);                                                        // execute the process and reset timer
    pthread_mutex_unlock(&t->lock);
}