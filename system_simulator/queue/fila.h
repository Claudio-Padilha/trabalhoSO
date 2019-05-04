#ifndef  FILA_H
#define  FILA_H

    #include <processo.h>
    #include <pthread.h>

    // Lists representing entry queue and ready queue
    // entry queue
    typedef struct queue    
    {
        process * first;
        process * last;     
    } queue;
    // mutex for entry queue       
    pthread_mutex_t entryLock = PTHREAD_MUTEX_INITIALIZER;

    // mutex for ready queue
    pthread_mutex_t readyLock = PTHREAD_MUTEX_INITIALIZER;
    // receives a queue, remove the first process from it and return the removed process
    process * removeFirst (queue * q);

    // receives a process  and a queue and inserts the process into the end of the queue. Returns pid
    int insert (process * p,queue * q);
#endif