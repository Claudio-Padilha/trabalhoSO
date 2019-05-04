#include <pthread.h>
#include <stdlib.h>
#include "memoria.h"
#include "../processo.h"
#include "../dbg.h"

memory *newMemory(int size) {
	memory *m = malloc(sizeof(memory));
	check(m != NULL, "failed to malloc memory");

	pthread_mutex_init(&(m->lock), NULL);

	m->first = NULL;
	m->used = 0;
	m->size = size;

	return m;
error:
	return NULL;
}
