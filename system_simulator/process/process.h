#ifndef  PROCESS_H
#define  PROCESS_H

#include <stdlib.h>

typedef struct process {
	int id;         
	int arrivalTime;         // moment a process enters entry queue
	int burstTime;           // CPU burst time
	int size;
	int memPosition;         // this is the initial adress of the process in memory. -1 when process not in memory 
} process;

// creates a new process
process * newProcess (int id, int size, int arrival, int burst);

#endif
