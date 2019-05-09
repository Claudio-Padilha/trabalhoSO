#ifndef  QUEUE_H
#define  QUEUE_H

    #include <process.h>
    #include <pthread.h>
    #include <stdlib.h>

    // Lists representing entry queue and ready queue
    // entry queue
    typedef struct queue    
    {
        process * first;
        process * last;  
        pthread_mutex_t lock;  
    } entryQueue;

    //ready queue
     typedef struct queue    
    {
        process * first;
        process * last;  
        pthread_mutex_t lock;  
    } readyQueue;

     // creates new entry queue
    newEntryQueue();

    // creates new ready queue
    newReadyQueue();

    // receives a queue, remove the first process from it and return the removed process
    process * removeFirst (struct queue * q);

    // receives a process  and a queue and inserts the process into the end of the queue. Returns pid
    int insert (process * p, struct queue * q);

#endif