#include "memory.h"

memory * newMemory (int size)
{
    memory * m = (memory *) malloc(sizeof(memory));
    m->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    m->size = size;
    m->used = 0;
    m->biggestInterval = size;

    return m;
}

process * copyFromMemory (int pid, memory * m)
{
     process * p = m->list;

     while (p != NULL && pid != p->id)
    {
        p = p->next;
    }

    return p;
}

process * getFromMemory (int pid, memory * m)
{
    process * p = m->list;                                                      // gets first element of the list
    process * prev = NULL;

    while (p != NULL && pid != p->id)
    {
        prev = p;
        p = p->next;
    }
    if (p != NULL)                                                              // process is in memory
    {   
        int newInterval = 0;
        if (p == m->list && p->next == NULL)                                    // It was the only process
        {
             m->list = p->next;                                                // Removes reference from memory
             newInterval = m->size;                                            // Gets the size of the new created interval
        }
        else if (p == m->list)                                                  // It was the first process
        {
             m->list = p->next;                                                // Removes reference from memory
             // Gets the size of the new created interval
             newInterval = p->size + (p->next->memPosition - (p->memPosition + p->size));   
        }
        else if (p != m->list && p->next == NULL)                               // It was the last process
        {
            newInterval = p->size + (p->memPosition - (prev->memPosition + prev->size));
        }
        else                      
        {
            // Gets the size of the new created interval
            newInterval = p->size + (p->next->memPosition - (p->memPosition + p->size)) + (p->memPosition - (prev->memPosition + prev->size));
            prev->next = p->next;                                              // Removes reference from memory 
        }

        if (m->biggestInterval < newInterval)
        {
            m->biggestInterval = newInterval;                                 // Adjusts biggestInterval if necessary
        }

        p->next = NULL;                                                       // Removes reference for process in memory
        p->memPosition = -1;                                                  // Adjusts memPosition atribute
    }

    return p;
}

process * firstFromMemory (memory * m) 
{
    process * ret = NULL;
    if (m->list != NULL)
    {
        ret = m->list;                              // gets process from memory
        m->list = m->list->next;                    // removes process reference from memory
        ret->memPosition = -1;                      // updates process memory position (none)
        
         // TODO: adjust biggestInterval if necessary
    }
    
    return ret;     
}

int insertIntoMemory (process * p, memory * mem, disk * d)                
{ 
    process * aux = mem->list;                                     // Gets first process
    if (aux == NULL)                                             // Memory is empty.
    {
        mem->list = p;
        p->memPosition = 0;
        mem->biggestInterval = mem->size - p->size;

        return p->id;
    }
    else
    {
        if (mem->biggestInterval >= p->size)                                // there is space in memory
        {
            while (aux->next != NULL)                                      // Looks for a space to fit the process p between processes
            {   
                if (aux->next->memPosition - (aux->memPosition + aux->size) >= p->size)         // there is space between processes
                {
                    p->next = aux->next;
                    aux->next = p;
                    p->memPosition = aux->memPosition + 1;

                     // TODO: adjust biggestInterval if necessary

                    return p->id;
                }
            }

            if (mem->size - 1 - (aux->memPosition + aux->size) >= p->size)    // There is space to put the process in the last position of the memory
            {
                aux->next = p;
                p->memPosition = aux->memPosition + 1;

                // TODO: adjust biggestInterval if necessary

                return p->id;
            }
        }


        // It's necessary to move process(es) from memory to disk                                                            
        process * aux;
        while (mem->list->memPosition < p->size)                      // Assumes a process is never to big for memory
        {   
            aux = firstFromMemory(mem);                                 // Removes process from memory
            insertIntoDisk(aux, d);                                   // Insert process into disk
        }

        p->memPosition = 0;                                           // Insert process in the begining of the memory
        p->next = mem->list;                                          
        mem->list = p;                                                

        return p->id;
    }

    return -1;                                                              // unknow error                                                         
}