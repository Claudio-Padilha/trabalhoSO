#ifndef  QUEUE_H
#define  QUEUE_H

    #include "../process/process.h"
    #include <stdio.h>
    #include <pthread.h>
    #include <stdlib.h>

    // Queue node structure
     typedef struct node    
    {
        int pid; 
        int burst;
        int size; 
        struct node * next;
    } node;

    // Lists representing entry queue and ready queue
    typedef struct queue    
    {
        node * first;
        node * last;  
        pthread_mutex_t lock;  
    } queue;

     // Creates new queue
    queue * newQueue();

    // Receives a queue, remove the first process from it and return the removed process pid. Returns -1 if process not in queue.
    int removeFromQueue (queue * q);

    // Receives a process pid and a queue and inserts the process into the end of the queue. Returns pid or -1 if it couldn't insert.
    int insertIntoQueue (int pid, int burst, int size, queue * q);

#endif