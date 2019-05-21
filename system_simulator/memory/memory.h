#ifndef  MEMORY_H
#define  MEMORY_H

	#include <pthread.h>
	#include <stdlib.h>
	#include "../disk/disk.h"
	#include "../process/process.h"

	typedef struct memory      
	{
		// Memory is represented by a list. This points to the first process of the list. Each process points to the next. It is ordered by pid.
		process * list;      
		// Amount of memory used
		int used;
		// Biggest continuous part of memory
		int biggestInterval;
		// Memory size
		int size;
		// Memory mutex
		pthread_mutex_t lock;
	}memory;

	// Creates a new memory. Returns null if something went wrong
	memory * newMemory (int size);

	// Gets the size of the biggest interval in memory and returns it
	int getBiggestInterval (memory * mem);

	// Gets a reference for a process tha is in memory. If returns null, process not in memory
	process * copyFromMemory (int pid, memory * mem);

	// Removes a process from the initial part of the memory
	process * firstFromMemory (memory * m);

	// Removes a process from memory and returns the process. Returns Null if the process is not in memory
	process * getFromMemory (int pid, memory * m);

	// Inserts a process into memory. Removes process(es) from memory and put into disk if necessary. Uses first fit
	int InsertIntoMemory (process * p, memory * mem, disk * d);
	
#endif
					