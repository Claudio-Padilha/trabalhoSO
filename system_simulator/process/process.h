#ifndef  PROCESS_H
#define  PROCESS_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <pthread.h>

    typedef struct process 
    {
        int id;         
        int arrivalTime;         // moment a process enters entry queue
        int burstTime;           // CPU burst time
        int size;
        int memPosition;         // this is the initial adress of the process in memory. -1 when process not in memory 
        
        struct process * next;  // when in memory or queue points to the next process
    } process;

    // creates a new process
    process * newProcess (int id, int size, int arrival, int burst);

#endif