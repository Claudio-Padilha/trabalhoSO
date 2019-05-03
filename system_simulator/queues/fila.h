#ifndef  FILA_H
#define  FILA_H

    #include <processo.h>

    // Lists representing entry queue and ready queue
    // entry queue
    typedef struct queue    
    {
        process * first;
        process * last;         
    }queue;

    // receives a queue, remove the first process from it and return the removed process
    process * removeFirst (queue q);

    // receives a process  and a queue and inserts the process into the end of the queue
    int insert (process * p, queue q);
#endif