#ifndef  CPU_H
#define  CPU_H

#include "../process/process.h"

// Consumes burst time from process. Consumes time quantum if burst is enough or consumes the remaining burst. Returns the amount of CPU used.
int cpu (process * p, int tq);
#endif