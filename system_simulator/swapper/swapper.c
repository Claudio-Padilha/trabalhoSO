#include "swapper.h"

int getBiggestInterval (memory * mem) 
{
    process * aux = mem->storage;
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

process * copyFromDisc (int pid, disc * d)
{
    process * p = NULL;                                                      // gets first element of the list
    for (int i =0; i<d->numberProcess; i++)
    {
        if (d->storage[i]->id == pid)
        {
            p = d->storage[i];
        }
    }
    
    return p;
}

process * firstFromMemory (memory * m) 
{
    process * ret = NULL;
    if (m->storage != NULL)
    {
        ret = m->storage;                              // Gets process from memory
        m->storage = m->storage->next;                    // Removes process reference from memory
        ret->memPosition = -1;                      // Updates process memory position (none)
        
        if (m->storage == NULL)
        {
            m->biggestInterval = m->size;
        }
        else if (m->storage->memPosition > m->biggestInterval)      
        {
            m->biggestInterval = m->storage->memPosition;          // Adjusts biggest interval if necessary
        }
    }
    
    return ret;     
}

int insertIntoMemory (process * p, memory * mem)                
{ 

    struct tm * currentTime;
    time_t segundos;

    process * aux = mem->storage;                                     // Gets first process
    if (aux == NULL)                                             // Memory is empty.
    {

        time(&segundos);   
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Swapper percebe que ha espaco no processo %d na memoria.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, p->id);

        mem->storage = p;
        p->memPosition = 0;
        mem->biggestInterval = mem->size - p->size;

        return p->id;
    }
    else                                                        // Memory is not empty
    {
        if (mem->biggestInterval >= p->size)                                // There is space in memory
        {

            time(&segundos);   
            currentTime = localtime(&segundos);
            printf("Time: %d:%d:%d - Swapper percebe que ha espaco para o processo %d na memoria.\n", 
            currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, p->id);
            
            if (aux->memPosition >= p->size)                                // There is space to put process in the first positon of memory
            {
                p->next = mem->storage;
                mem->storage = p;
                if (aux->memPosition == mem->biggestInterval)
                {
                    mem->biggestInterval = getBiggestInterval(mem);
                }

                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Swapper traz o processo %d do disco e o coloca na memoria.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, p->id);
                return p->id;
            }

            while (aux->next != NULL)                                      // Looks for a space to fit the process p between processes
            {   
                if (aux->next->memPosition - (aux->memPosition + aux->size) >= p->size)         // there is space between processes
                {
                    p->next = aux->next;
                    aux->next = p;
                    p->memPosition = aux->memPosition + aux->size;

                    mem->biggestInterval = getBiggestInterval (mem);

                    time(&segundos);   
                    currentTime = localtime(&segundos);
                    printf("Time: %d:%d:%d - Swapper traz o processo %d do disco e o coloca na memoria.\n", 
                    currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, p->id);

                    return p->id;
                }

                aux = aux->next;
            }

            if (mem->size - 1 - (aux->memPosition + aux->size) >= p->size)    // There is space to put the process in the last position of the memory
            {
                aux->next = p;
                p->memPosition = aux->memPosition + aux->size;
                mem->biggestInterval = getBiggestInterval (mem);

                time(&segundos);   
                currentTime = localtime(&segundos);
                printf("Time: %d:%d:%d - Swapper traz o processo %d do disco e o coloca na memoria.\n", 
                currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, p->id);

                return p->id;
            }
        }

        time(&segundos);   
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Swapper percebe que nao ha espaco no processo %d na memoria.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, p->id);

        // It's necessary to move process(es) from memory to disk                                                            
        process * aux;
        while (mem->storage != NULL && mem->storage->memPosition < p->size)                      // Assumes a process is never too big for memory
        {   
            aux = firstFromMemory(mem);                                 // Removes first process from memory
            time(&segundos);   
            currentTime = localtime(&segundos);
            printf("Time: %d:%d:%d - Swapper retirou o processo %d para liberar espaco na memoria, e o enviou ao disco.\n", 
            currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, aux->id);
        }

        p->memPosition = 0;                                           // Insert process in the begining of the memory  
        p->next = mem->storage;                                          
        mem->storage = p;  

        time(&segundos);   
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Swapper traz o processo %d do disco e o coloca na memoria.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, p->id);  

        if (mem->storage->next == NULL)                                // Process is alone in memory
        {
            mem->biggestInterval = mem->size - mem->storage->size;
        } else if ((mem->storage->next->memPosition - mem->storage->size) > mem->biggestInterval)     // New biggest interval is necessary
        {
            mem->biggestInterval = (mem->storage->next->memPosition - mem->storage->size);
        }                                   

        return p->id;
    }

    return -1;                                                              // unknow error                                                         
}

void * swapper (void * param)
{
    swapperArgs * swArgs = (swapperArgs *) param;

    pthread_mutex_lock(&swArgs->d->lock);
    pthread_mutex_lock(&swArgs->m->lock);
    process * p = copyFromDisc(swArgs->pid, swArgs->d);
    insertIntoMemory(p, swArgs->m);
    pthread_mutex_unlock(&swArgs->d->lock);
    pthread_mutex_unlock(&swArgs->m->lock);

    return NULL;
}