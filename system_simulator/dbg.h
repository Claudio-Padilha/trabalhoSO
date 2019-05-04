#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>

#define check(A, M) if (!(A)) {\
	fprintf(stderr, "[ERROR] (%s:%d)" M "\n", __FILE__, __LINE__); goto error;}

#define check_mem(A) check((A), "Out of memory") 

#endif
