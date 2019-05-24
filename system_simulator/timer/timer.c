#include "timer.h"

timer * newTimer(int tq, int numberProcesses)
{
    timer * t = (timer *) malloc(sizeof(timer));
    t->timeQuantum = tq;
    t->numberProcesses = numberProcesses;
    t->endedProcesses = 0;
    t->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    t->condTq = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    t->condBurst = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    t->condEnd = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    return t;   
}

void * resetTimer (void * param)
{
    timerArgs * args = (timerArgs *) param;

    sleep(args->cpuUsage);
    
    struct tm * currentTime;
    time_t segundos;

    if (args->ended)                                                    // Process ended burst time
    {
        args->t->endedProcesses ++;

        time(&segundos);   
        currentTime = localtime(&segundos);
        printf("Time: %d:%d:%d - Processo %d terminou sua execucao.\n", 
        currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, args->pid);

        pthread_cond_broadcast(&args->t->condBurst);                       // Signals to FCFS
    }

    time(&segundos);   
    currentTime = localtime(&segundos);
    printf("Time: %d:%d:%d - Timer informa ao Escalonador Round-Robin de CPU que o processo %d atualmente em execucao precisa ser retirado da CPU.\n", 
    currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, args->pid);

    pthread_cond_broadcast(&args->t->condBurst);                            // Signals to Round Robin 

    if (args->t->numberProcesses == args->t->endedProcesses)              // All processes ended
    {
        pthread_cond_broadcast(&args->t->condEnd);                        // Signals the end of the execution to simulaotr
    }   

    return NULL;
}