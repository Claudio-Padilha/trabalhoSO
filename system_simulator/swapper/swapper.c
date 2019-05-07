#include <swapper.h>

int processIntoMemory (process * p, memory * mem, disk * d)       
{ 
    if (mem->list == NULL)                                             // Memory is empty.
    {
        mem->list = p;
        p->memPosition = 0;
        mem->used += p->size;

        return p->id;
    }
    else
    {
        process * aux = mem->list;                                     // Gets first process

        while (aux->next != NULL)                                      // Looks for a space to fit the process p between processes
        {   
            if (aux->next->memPosition - (aux->memPosition + aux->size) >= p->size)
            {
                p->next = aux->next;
                aux->next = p;
                p->memPosition = aux->memPosition + 1;

                mem->used += p->size;

                return p->id;
            }
        }

        if (mem->size - 1 - (aux->memPosition + aux->size) >= p->size)    // There is space to put the process in the last position of the memory
        {
            aux->next = p;
            p->memPosition = aux->memPosition + 1;

            mem->used += p->size;

            return p->id;
        }
        else                                                              // It's necessary to move process(es) from memory to disk                                                            
        {
            aux = mem->list;
            while (mem->list->memPosition < p->size)
            {   
                processIntoDisk(aux, d);
                aux = aux->next;
                if (aux == NULL)
                {
                    printf ("process %d too big", p->id);                  // process too big for memory. returns error
                    return -1;
                }
            }

            p->memPosition = 0;
            p->next = aux;                                                 // here we remove from memory the 
            mem->list = p;                                                 // processes that went to disk

            return p->id;
        }
        
    }

    return -1;                                                              // unknow error                                                         
}

void * swapp (int pid, disk * d, memory * mem)
{
   
    pthread_mutex_lock(&d->lock);                                       // aquire disk lock
    pthread_mutex_lock(&mem->lock);                                     // aquire memory lock
        process * p = getFromDisk(pid, d)                               // gets a process from disk

        processIntoMemory(p, mem, d)                                    // puts the process into memory
            
    pthread_mutex_unlock(&mem->lock);                                   // releases memory lock
    pthread_mutex_unlock(&d->lock);                                     // releases disk lock

    return p;
}