#ifndef  MEMORY_H
#define  MEMORY_H

	#include <pthread.h>
	#include <stdlib.h>

	typedef struct memory      
	{
		// memory is represented by a list. This points to the first process of the list. Each process points to the next. It is ordered by pid.
		process * list;      
		// amount of memory used
		int used;
		// memory size
		int size;
		// memory mutex
		pthread_mutex_t lock;
	}memory;

	// creates a new memory. Returns null if something went wrong
	memory * newMemory ();

	// looks for a process in memory. Returns NULL if process not in memory. Doesn't remove the process from memory, just gets a pointer to the process.
	process * lookForProcess (int pid, memory * m);
	
#endif
	