#include "cpu.h"

int cpu (process * p, int tq)
{
        int ret = tq;                           // Assumes tq < process burst

        if (p->burst > tq)
        {
                p->burst -= tq;        
        }else {
                ret = p->burst;
                p->burst = 0;
        }

        return ret;    
}