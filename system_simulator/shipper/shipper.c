#include "shipper.h"

void * shipper (void * param)
{
    int flag = 0;                                                                   // Indicates if a process ended bursttime

    shipperArgs * args = (shipperArgs *) param;
    pthread_mutex_lock(&args->mem->lock);                       
    pthread_mutex_lock(&args->d->lock);
    pthread_mutex_lock(&args->ready->lock);

        process * p = copyFromMemory(args->pid, args->mem);                         // Tries to coppy the  process from memory. There is still a reference in memory

        struct tm * currentTime;                                                    // used to print time
        time_t segundos;

        if (p == NULL)                                                              // process not in memory
        {
            time(&segundos);   
            currentTime = localtime(&segundos);
            printf("Time: %d:%d:%d - Despachante percebe que o processo id esta no disco e solicita que o Swapper traga %d a memoria.\n", 
            currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, args->pid); 
            swappArgs * sw = malloc(sizeof(swappArgs));
            sw->d = args->d;                                                         // aquire arguments for swapper in a structure
            sw->mem = args->mem;
            sw->pid = args->pid;

            pthread_t swa;
            pthread_create(&swa, NULL, swapper, (void *) sw);                      // call swapper as a thread
            pthread_join(swa, NULL);                                               // Waits untill swapper brings process from disk to memory

            time(&segundos);   
            currentTime = localtime(&segundos);
            printf("Time: %d:%d:%d - Despachante eh avisado pelo Swapper que o processo %d esta na memoria.\n", 
            currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, args->pid);

            p = copyFromMemory(args->pid, args->mem);                         // Copies the  process from memory. There is still a reference in memory   
        }

        time(&segundos);   
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Despachante percebe que o processo %d esta na memoria.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, args->pid); 

        pthread_mutex_lock(&args->t->lock);
        int cpuTime = workOnProcess(p, args->t->timeQuantum);                   // Consumes tq or burstLeft (whichever is smaller) of process burst time and returns it
        pthread_mutex_unlock(&args->t->lock);
        if (p->burstTime < 0)
        {
            flag = 1;
        }
        
        timerArgs * tmArgs = (timerArgs *) malloc(sizeof(timerArgs));
        tmArgs->cpuUsage = cpuTime;
        tmArgs->t = args->t;
        tmArgs->ended = flag;
        tmArgs->pid = p->id;
        
    pthread_mutex_unlock(&args->mem->lock);                       
    pthread_mutex_unlock(&args->d->lock);
    pthread_mutex_unlock(&args->ready->lock);

    pthread_t tm;
    pthread_create(&tm, NULL, resetTimer, (void *) tmArgs);                         // reset the timer

    if (p->burstTime > 0)                                       
    {   
        pthread_mutex_lock(&args->ready->lock);
        insertIntoQueue(p->id, p->burstTime, p->size, args->ready);             // Puts process back in ready queue if it still has burstTime
        pthread_mutex_unlock(&args->ready->lock);
    }

    currentTime = localtime(&segundos);
    printf("Time: %d:%d:%d - Despachante reiniciou o Timer com tq e liberou a CPU ao processo %d.\n", 
    currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, args->pid); 

    return NULL;
}