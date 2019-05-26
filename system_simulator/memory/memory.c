#include "memory.h"

memory * newMemory (int size)
{
    memory * ret = malloc(sizeof(memory));
    ret->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    ret->storage = NULL;
    ret->size = size;
    ret->biggestInterval = size;
    
    return ret;
}