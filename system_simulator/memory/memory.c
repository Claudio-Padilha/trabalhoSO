#include "memory.h"

memory * newMemory (int size)
{
    memory * m = (memory *) malloc(sizeof(memory));
    m->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    m->size = size;
    m->biggestInterval = size;

    return m;
}

int getBiggestInterval (memory * mem) 
{
    process * aux = mem->list;
    int biggest = 0;

    while (aux->next != NULL)                                           // Verifies which interval (except the last one) is the biggest
    {
        if ((aux->next->memPosition - (aux->memPosition + aux->size)) > biggest)
        {
            biggest = aux->next->memPosition - (aux->memPosition + aux->size);
        }

        aux = aux->next;
    }

    if (((mem->size - 1) - (aux->memPosition + aux->size)) > biggest)    // Verifies if the last interval is bigger than current biggest
    {
        biggest = (mem->size - 1) - (aux->memPosition + aux->size);
    }

    return biggest;   
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
        else                                                                    // It was between processes        
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
        ret = m->list;                              // Gets process from memory
        m->list = m->list->next;                    // Removes process reference from memory
        ret->memPosition = -1;                      // Updates process memory position (none)
        
        if (m->list->memPosition > m->biggestInterval)      
        {
            m->biggestInterval = m->list->memPosition;          // Adjusts biggest interval if necessary
        }
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
    else                                                        // Memory is not empty
    {
        if (mem->biggestInterval >= p->size)                                // There is space in memory
        {
            int flag = 0;                                                   // Control for biggestInterval adjustment (if necessary)
            while (aux->next != NULL)                                      // Looks for a space to fit the process p between processes
            {   
                if (aux->next->memPosition - (aux->memPosition + aux->size) >= p->size)         // there is space between processes
                {
                    if ((aux->next->memPosition - (aux->memPosition + aux->size)) == mem->biggestInterval)  // It is necessary to adjust biggestInterval
                    {
                        flag = 1;
                    }
                    
                    p->next = aux->next;
                    aux->next = p;
                    p->memPosition = aux->memPosition + aux->size;

                     if (flag == 1)                                     // It is necessary to adjust biggest interval
                     {
                        mem->biggestInterval = getBiggestInterval (mem);
                     }

                    return p->id;
                }

                aux = aux->next;
            }

            if (mem->size - 1 - (aux->memPosition + aux->size) >= p->size)    // There is space to put the process in the last position of the memory
            {
                if (mem->size - 1 - (aux->memPosition + aux->size) == mem->biggestInterval) // Process insertion will affect biggestInterval size
                {
                    flag == 1;
                }
                aux->next = p;
                p->memPosition = aux->memPosition + aux->size;

                 if (flag == 1)                                             // It is necessary to adjust biggest interval
                {
                    mem->biggestInterval = getBiggestInterval (mem);
                }

                return p->id;
            }
        }


        // It's necessary to move process(es) from memory to disk                                                            
        process * aux;
        while (mem->list->memPosition < p->size)                      // Assumes a process is never too big for memory
        {   
            aux = firstFromMemory(mem);                                 // Removes first process from memory
            insertIntoDisk(aux, d);                                   // Insert process into disk
        }

        p->memPosition = 0;                                           // Insert process in the begining of the memory
        p->next = mem->list;                                          
        mem->list = p;    

        if (mem->list->next == NULL)                                // Process is alone in memory
        {
            mem->biggestInterval == mem->size - mem->list->size;
        } else if ((mem->list->next->memPosition - mem->list->size) > mem->biggestInterval)     // New biggest interval is necessary
        {
            mem->biggestInterval = (mem->list->next->memPosition - mem->list->size);
        }                                   

        return p->id;
    }

    return -1;                                                              // unknow error                                                         
}