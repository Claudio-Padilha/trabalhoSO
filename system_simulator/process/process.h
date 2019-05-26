#ifndef  PROCESS_H
#define  PROCESS_H

#include <stdlib.h>

typedef struct process
{   
    // Process atributes.
    int id;
    int size;
    int creation;
    int burst;
    int memPosition;

    // pointer to the next process.
    struct process * next;
}process;

// Creates a new process
process * newProcess (int pid, int size, int creation, int burst);

#endif