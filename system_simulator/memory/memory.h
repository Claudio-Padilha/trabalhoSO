#ifndef  MEMORY_H
#define  MEMORY_H

	#include <pthread.h>
	#include <stdlib.h>
	#include "../disk/disk.h"
	#include "../process/process.h"

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

	// looks for a process in memory. Returns true (1) if process is in memory. Returns false (0) if process is not in memory
	int isInMemory (int pid, memory * m);

	// Removes a process from the initial part of the memory
	process * getFromMemory (memory * m);

	// Inserts a process into memory. Removes process(es) from memory and put into disk if necessary. Uses first fit
	int InsertIntoMemory (process * p, memory * mem, disk * d);
	
#endif
					