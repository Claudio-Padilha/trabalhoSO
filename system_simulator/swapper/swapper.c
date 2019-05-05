#include <swapper.h>

void * swapp (int pid, disk * d, memory * mem)
{
   
    pthread_mutex_lock(&d->lock);                                       // aquire disk lock
        process * p = getFromDisk(pid, d)                               // gets a process from disk
        pthread_mutex_lock(&mem->lock);                                     // aquire memory lock 
            if (mem->size - mem->used >= p->size)                          // verifies if there is space in memory
            {
                int ret = processIntoMemory(p, mem);                            // puts a process into memory
            }
            else                                                        // there isn't enough space in memory
            {
                
            }    
            
        pthread_mutex_unlock(&mem->lock);                                   // releases memory lock
    pthread_mutex_unlock(&d->lock);                                     // releases disk lock

    return ret;
}