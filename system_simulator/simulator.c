#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "cpu/cpu.h"
#include "creator/creator.h"
#include "disk/disk.h"
#include "memory/memory.h"
#include "process/process.h"
#include "queue/queue.h"
#include "scheduler/scheduler.h"
#include "shipper/shipper.h"
#include "swapper/swapper.h"
#include "timer/timer.h"

int main ()
{
    int memorySize;
    int numberProcesses;
    int timeQuantum;
    int pid;
    int processSize;
    int creationTime;
    int burst;
    process * p = NULL;

    if (scanf("%d %d %d", &memorySize, &numberProcesses, &timeQuantum))         // Reads main memory size, number of processes and time quantum parameters.
    {}  // if avoids warning

    disk * d = newDisk();                                                           // Creates new disk
    memory * m = newMemory(memorySize);                                             // Creates new memory
    queue * entry = newQueue();                                                     // Creates new entry queue
    queue * ready = newQueue();                                                       // Creates new ready queue
    timer * t = newTimer(timeQuantum, numberProcesses);                                    // Creates new timer

    struct tm * currentTime;
    time_t segundos;
    time(&segundos);   
    currentTime = localtime(&segundos);
    printf("Time: %d:%d:%d - Inicio da observacao.\n", currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);

    pthread_t fcfs;
    fcfsArgs * fcArgs = (fcfsArgs *) malloc(sizeof(fcfsArgs));
    fcArgs->d = d;
    fcArgs->entry = entry;                                                          // Gets arguments for FCFS scheduler
    fcArgs->mem = m;
    fcArgs->ready = ready;
    fcArgs->t = t;
    
    pthread_create(&fcfs, NULL, schedulerFCFS, (void *) fcArgs);                    // Creates scheduler FCFS

    pthread_t rr;
    rrArgs * roundArgs = (rrArgs *) malloc(sizeof(rrArgs));
    roundArgs->d = d;
    roundArgs->mem = m;                                                            // Gets arguments for RR scheduler
    roundArgs->ready = ready;           
    roundArgs->t = t;

    pthread_create(&rr, NULL, schedulerRR, (void *) roundArgs);                    // Creates scheduler RR

    for (int i = 0; i < numberProcesses; i++)                               
    {
        if(scanf("%d %d %d %d", &pid, &processSize, &creationTime, &burst))      // Reads a process parameters. 
        {}  // if avoids warning
        p = newProcess(pid, processSize, creationTime, burst);                      // Creates the processes

        pthread_mutex_lock(&d->lock);
            insertIntoDisk(p, d);                                                   // Puts created process in disk
        pthread_mutex_unlock(&d->lock);

        pthread_t cr;
        creatorArgs * crArgs = (creatorArgs *) malloc(sizeof(creatorArgs));
        crArgs->entry = entry;
        crArgs->p = p;
        pthread_create(&cr, NULL, creator, (void *) crArgs);                        // Creates a creator thread for each process
    }

    pthread_cond_wait(&t->condEnd, &t->lock);                           // Waits for timer signal to end the execution

    time(&segundos);   
    currentTime = localtime(&segundos);
    printf("Time: %d:%d:%d - Termino da observacao.\n", currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);

    return 0;
}