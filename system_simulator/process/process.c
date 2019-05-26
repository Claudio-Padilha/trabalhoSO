#include "process.h"

process * newProcess (int pid, int size, int creation, int burst)
{
    process * ret = malloc(sizeof(process));
    ret->id = pid;
    ret->size = size;
    ret->creation = creation;
    ret->burst = burst;
    ret->memPosition = -1;
    
    ret->next = NULL;

    return ret;
}