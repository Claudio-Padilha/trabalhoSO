#include "process.h"

process * newProcess (int id, int size, int arrival, int burst) {
    process * p = malloc(sizeof(process));
	if (p == NULL) return NULL;

    p->id = id;
    p->size = size;
    p->arrivalTime = arrival;
    p->burstTime = burst;
    p->memPosition = -1;

    return p;
}
