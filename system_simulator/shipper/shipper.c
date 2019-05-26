#include "shipper.h"

void * shipper (void * param)
{
    shipperArgs * shArgs = (shipperArgs *) param;

    struct tm * currentTime;                                                    // used to print time
    time_t segundos;

    pthread_mutex_lock(&shArgs->m->lock);

    process * p = shArgs->m->storage;

    while(p != NULL && p->id != shArgs->pid)                        // Looks for process in memory.
    {
        p = p->next;
    }

    pthread_mutex_unlock(&shArgs->m->lock);

    if (p != NULL)                                                  // Process is in memory
    {
        time(&segundos);   
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Despachante percebe que o processo %d esta na memoria.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, shArgs->pid); 

        time(&segundos);
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Despachante reiniciou o Timer com tq e liberou a CPU ao processo %d.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, shArgs->pid);

        int cpuTime = cpu(p, shArgs->tq);

        timerArgs * tmArgs = malloc(sizeof(timerArgs));
        tmArgs->cpuUsage = cpuTime;
        if (p->burst == 0) 
        {
            tmArgs->ended = 1;
        }
        else
        {
            tmArgs->ended = 0;
        }
        tmArgs->pid = p->id;
        pthread_mutex_lock(&shArgs->t->lock);
        tmArgs->t = shArgs->t;
        pthread_mutex_unlock(&shArgs->t->lock);
        
        pthread_t tm;
        pthread_create(&tm, NULL, resetTimer, (void *) tmArgs);                         // reset the timer
        return NULL;   
    }
    else                                                            // Process not in memory
    {
        time(&segundos);   
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Despachante percebe que o processo id esta no disco e solicita que o Swapper traga %d a memoria.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, shArgs->pid); 


        pthread_mutex_lock(&shArgs->d->lock);
        pthread_mutex_lock(&shArgs->m->lock);
        swapperArgs * swArgs = malloc(sizeof(swapperArgs));
        swArgs->d = shArgs->d;
        swArgs->m = shArgs->m;
        swArgs->pid = shArgs->pid;
        pthread_mutex_unlock(&shArgs->d->lock);
        pthread_mutex_unlock(&shArgs->m->lock);

        pthread_t swa;
        pthread_create(&swa, NULL, swapper, (void *) swArgs);                   // call swapper as a thread
        pthread_join(swa, NULL);                                               // Waits untill swapper brings process from disk to memory

        time(&segundos);   
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Despachante eh avisado pelo Swapper que o processo %d esta na memoria.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec,shArgs->pid);

        pthread_mutex_lock(&shArgs->m->lock);

        p = shArgs->m->storage;
        while(p != NULL && p->id != shArgs->pid)                        // Looks for process in memory.
        {
            p = p->next;
        }
        pthread_mutex_unlock(&shArgs->m->lock);

        time(&segundos);
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Despachante reiniciou o Timer com tq e liberou a CPU ao processo %d.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, shArgs->pid);

        int cpuTime = cpu(p, shArgs->tq);

        timerArgs * tmArgs = malloc(sizeof(timerArgs));
        tmArgs->cpuUsage = cpuTime;
        if (p->burst == 0) 
        {
            tmArgs->ended = 1;
        }
        else
        {
            tmArgs->ended = 0;
        }
        tmArgs->pid = p->id;
        pthread_mutex_lock(&shArgs->t->lock);
        tmArgs->t = shArgs->t;
        pthread_mutex_unlock(&shArgs->t->lock);
        
        pthread_t tm;
        pthread_create(&tm, NULL, resetTimer, (void *) tmArgs);                         // reset the timer
        return NULL;   
    }
    
}