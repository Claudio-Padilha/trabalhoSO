#include "memory.h"

memory * newMemory ()
{
    memory * m = (memory *) malloc(sizeof(memory));
    m->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return m;
}

int isInMemory (int pid, memory * m)
{
    process * aux = m->list;

    while (aux != NULL && aux->id != pid)                   // Looks for process              
    {
        aux = aux->next;
    }

    if (aux == NULL)                                        // Process not in memory
    {
        return 0;                                           
    }

    return 1;                                               // Process is in memory
}

process * getFromMemory (memory * m) 
{
    process * ret = NULL;
    if (m->list != NULL)
    {
        ret = m->list;                              // gets process from memory
        m->list = m->list->next;                    // removes process reference from memory
        m->used -= ret->size;                       // updates used memory atribute
        ret->memPosition = -1;                      // updates process memory position (none)
    }
    
    return ret;     
}

int insertIntoMemory (process * p, memory * mem, disk * d)                
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
            process * aux;
            while (mem->list->memPosition < p->size)                      // Assumes a process is never to big for memory
            {   
                aux = getFromMemory(mem);                                 // Removes process from memory
                insertIntoDisk(aux, d);                                   // Insert process into disk
            }

            p->memPosition = 0;                                           // Insert process in the begining of the memory
            p->next = mem->list;                                          
            mem->list = p;                                                

            return p->id;
        }
        
    }

    return -1;                                                              // unknow error                                                         
}