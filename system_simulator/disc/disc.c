#include "disc.h"

disc * newDisc (int numProcess)
{
    disc * ret = malloc(sizeof(disc));
    ret->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    ret->storage = malloc(sizeof(process *) * numProcess);
    ret->numberProcess = numProcess;

    return ret;
}

