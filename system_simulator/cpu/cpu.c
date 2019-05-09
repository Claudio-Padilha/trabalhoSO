#include <cpu.h>

int workOnProcess (process * p, int tq)
{
        int ret = tq;
        if (p->burstTime < tq)
        {
                p->burstTime -= tq;
        }else
        {
                ret = p->burstTime;
                p->burstTime = 0;
        }    
        return ret; 
}