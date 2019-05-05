#ifndef  PROCESS_H
#define  PROCESS_H

    typedef struct process 
    {
        int id;         
        int arrivalTime;         // moment a process enters entry queue
        int burstTime;           // CPU burst time
        int size;

        struct process * next;  // when in memory or queue points to the next process
    } process;

    // creates a new process
    process * newProcess (int id, int size, int arrival, int burst);

#endif