#ifndef  QUEUE_H
#define  QUEUE_H

#include "process.h"
#include <stdlib.h>
#include <pthread.h>


struct QueueNode;

typedef struct QueueNode {
	QueueNode *next;
	process *value;
} QueueNode;

// Lists representing entry queue and ready queue
// entry queue
typedef struct Queue {
    QueueNode * first;
    QueueNode * last;  
	int count;
    pthread_mutex_t lock;  
} Queue;

// creates new queue.
Queue *queueNew();

// receives a queue, remove the first process from it and return the removed process
process * queuePop(Queue * q);
process * queueSecurePop(Queue * q);

// Do the same as queuePop but without remove.
process * queuePeek(Queue * q);
process * queueSecurePeek(Queue * q);

// receives a process  and a queue and inserts the process into the end of the queue. Returns pid
int queuePush(Queue * q, process *p);
int queueSecurePush(Queue * q, process *p);

int queueSecureCount(Queue *q);
#endif
