#include "queue.h"

Queue *queueNew(){
	// Use calloc to malloc and zero all fields.
	Queue *q = calloc(1, sizeof(Queue));
	if (q == NULL) return NULL;
	
	pthread_mutex_init(&q->lock, NULL);
    return q;
}

// Remove the first of queue.
process *queuePop(Queue * q) {
	if (q->first == NULL) return NULL;

	Queue *node = q->first;
	process *p = node->value;

	if (node == q->last) {
		q->first = NULL;
		q->last = NULL;
	} else {
		q->first = node->next;
	}

	free(node);
	q->count--;	

	return p;
}

process *queueSecurePop(Queue *q) {
	pthread_mutex_lock(&q->lock);
	process *p = queuePop(q)	
	pthread_mutex_unlock(&q->lock);
	return p;
}

// Return the first process of queue 
// without remove node.
process *queuePeek(Queue * q) {
	if (q->first == NULL) return NULL;
	process *p = q->first->value;
	return p;
}
	
process *queueSecurePeek(Queue * q) {
	pthread_mutex_lock(&q->lock);
	process *p = queuePeek(q);
	pthread_mutex_unlock(&q->lock);
	return p;
}

// Insert at the last position of queue.
int queuePush(Queue *q, process *p) {
	QueueNode *node = calloc(1, sizeof(QueueNode));
	if (node == NULL) return -1;

	node->value = p;

	if (q->first == NULL && q->last == NULL) {
		q->first = node;
		q->last = node;
	} else {
		q->last->next = node;
		q->last = node;
	}

	q->count++;
	return p->id;
}

int queueSecurePush(Queue *q, process *p) {
	pthread_mutex_lock(&q->lock);
	int pid = queuePush(q, p);
	pthread_mutex_unlock(&q->lock);
	return pid;
}

int queueSecureCount(Queue *q) {
	pthread_mutex_lock(&q->lock);
	int count = q->count;
	pthread_mutex_unlock(&q->lock);
	return count;
}
