#include <shipper.h>

void * shipp (int pid, memory * mem, disk * d, timer * t)
{
    pthread_mutex_lock(&mem->lock);
        process * p = lookForProcess(pid, mem);                                        // try to get process from memory
    pthread_mutex_unlock(&mem->lock);
    
    if (p == NULL)                                                                // process not in memory
    {
        swapp(pid, d, mem);                                                       // swapps aquire all necessary locks and brings the process to memory
        pthread_mutex_lock(&mem->lock);
            p = lookForProcess(pid, mem);                                             // gets the  process from memory
        pthread_mutex_unlock(&mem->lock);
    }

    pthread_mutex_lock(&t->lock);
        resetTimer(p, t);                                                        // execute the process and reset timer
    pthread_mutex_unlock(&t->lock);
}