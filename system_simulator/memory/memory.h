#ifndef  MEMORY_H
#define  MEMORY_H

#include <pthread.h>
#include <stdlib.h>
#include "../process/process.h"
typedef struct memory
{
	// Memory atributes.
	int size;
	int biggestInterval;

	// storage represents the procesees currently in memory. Each process has a pointer to the next.
	process * storage;

	// Memory's lock.
	pthread_mutex_t lock;
}memory;

// Creates a new memory.
memory * newMemory (int size);
#endif
					