#include <memory.h>
memory * newMemory ()
{
    memory * m = (memory *) malloc(sizeof(memory));
    m->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return m;
} 