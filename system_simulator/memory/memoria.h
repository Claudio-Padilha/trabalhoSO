#ifndef  MEMORIA_H
#define  MEMORIA_H

    #include <pthread.h>

    // structure representing memory
    typedef struct memory
    {
        process * buffer;       // memory is represented by a list. This points to the first process of the list
        int used;               // amount of memory used          
        int size;               // total storage capacity
    } memory;

    // mutex for memory
    pthread_mutex_t memoryLock = PTHREAD_MUTEX_INITIALIZER;


#endif