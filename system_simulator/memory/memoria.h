#ifndef  MEMORIA_H
#define  MEMORIA_H

#include <pthread.h>
#include <processo.h>

typedef struct memory
{
 	// memory is represented by a list. This points to the first process of the list. NOT A BUFFER
	process * buffer;      
	// amount of memory used
	int used;
	// memory size
	int size;
} memory;

// memory mutex
pthread_mutex_t memoryLock = PTHREAD_MUTEX_INITIALIZER;

#endif
	