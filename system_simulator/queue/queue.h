#ifndef  QUEUE_H
#define  QUEUE_H

#include <pthread.h>
#include <stdlib.h>

// Struct representing the processes on the queue.
typedef struct node
{   
    // Process information.
    int pid;
    int burst;
    int size;

    // Pointer to the next node on queue.
    struct node * next;
}node;

// Struct representing the entry and ready queue.
typedef struct queue
{
    // begining of the queue.
    node * first;
    // end of the queue.
    node * last;

    // Queue's lock.
    pthread_mutex_t lock;
}queue;

// Creates a new node.
node * newNode (int pid, int burst, int size);

// Creates a new queue.
queue * newQueue ();

#endif