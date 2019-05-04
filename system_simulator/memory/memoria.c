#include <pthread.h>
#include "memoria.h"
#include "process.h"
#include "dbg.h"

memory *newMemory(int size) {
	memory *m = malloc(sizeof(memory));
	check(m != NULL, "failed to malloc memory");

	m->buffer = calloc(size, sizeof(process));
	check(m->buffer != NULL, "failed to malloc memory->buffer");

	m->lock = PTHREAD_MUTEX_INITIALIZER;
	m->used = 0;
	m->size = size;

	return memory;
error:
	return NULL;
}
