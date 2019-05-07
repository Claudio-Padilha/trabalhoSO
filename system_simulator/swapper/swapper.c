#include <swapper.h>

process * p getFromDisk (int pid, disk * d)
{
    process * p = d->list;                                                      // gets first element of the list
    process * prev = NULL;

    while (p != NULL && pid != p->id)
    {
        prev = p;
        p = p->next;
    }
    if (p == NULL)  
    {
        printf("ERROR! Process Loss")                                           // process not in disk
    }
    else                                                                       //  procces found. Pointers adjustment.
    {
        if (prev == NULL)
        {
            d->first = p->next;
        }else                      
        {
            prev->next = p->next;
        }
    }

    return p;
}

int swapperIntoDisk (process * p, disk * d)                                 
{
    if (d->first == NULL)                                                      // disk is empty
    {
        d->first = p;
        d->last = p;
    }
    else
    {
        process * aux = d->first;
        process * prev = NULL;

        while (aux->id < p->id) 
        {
            if (aux->next == NULL)
            {
                break;
            }
            prev = aux;
            aux = aux->next;
        }

        if (aux == disk->fisrt)                                                 // process goes in the first position
        {
            p->next = disk->first;
            disk->first = p;
        }
        else if (aux->next == NULL && aux->id < p->id)                          // process goes in the last position
        {
            d->last->next = p;
            d->last = p;
        }
        else                                                                // process goes between two other processes
        {
            prev->next = p;
            p->next = aux;        
        }
    }
    
}

int swapperIntoMemory (process * p, disk * d, memory * mem)       
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
        processIntoMemory(p, d, mem)                                    // puts the process into memory    
    pthread_mutex_unlock(&mem->lock);                                   // releases memory lock
    pthread_mutex_unlock(&d->lock);                                     // releases disk lock

    return p;
}