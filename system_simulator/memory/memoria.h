#ifndef  MEMORIA_H
#define  MEMORIA_H

#include <pthread.h>
#include "process.h"

typedef struct memory
{
	// lock is the memory mutex.
	pthread_mutex_t lock;
 	// memory is represented by a list. This points to the first process of the list.
	process * buffer;      
	// amount of memory used.
	int used;
	// size of buffer.
	int size;
} memory;

// newMemory creates and initilize a memory struct
// with buffer length of size.
memory *newMemory(int size);

#endif
