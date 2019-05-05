#include <cpu.h>



int workOnProcess (cpu * c, process * p, memory * mem)
{
        p->burstTime -= c->timeQuantum;
}