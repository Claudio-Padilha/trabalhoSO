#include "memory.h"

memory * newMemory ()
{
    memory * m = (memory *) malloc(sizeof(memory));
    m->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return m;
}

process * lookForProcess (int pid, memory * m)
{
    process * ret = memory->list;

    while (ret != NULL && ret->id != pid)
    {
        ret = ret->next;
    }

    return ret;
}