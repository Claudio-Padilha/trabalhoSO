#include <process.h>

process * newProcess (int id, int size, int arrival, int burst)
{
    process * p = (process *) malloc(sizeof(process));
    p->id = id;
    p-size = size;
    p->arrivalTime = arrival;
    p->burstTime = burst;

    return p;
}