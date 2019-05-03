#ifndef  PROCESSO_H
#define  PROCESSO_H

typedef struct process 
{
    int id;         
    int arrivalTime;         // moment a process enters entry queue
    int burstTime;           // CPU burst time
    int size;

    struct process * next;  // when in memory points to the next process of the list
} process;

#endif