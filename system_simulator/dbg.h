#ifndef __dbg.h__
#define __dbg.h__

#include <stdio.h>

#define check(A, M) if (!(A)) {\
	fprintf(stderr, "[ERROR] (%s:%d)" M "\n", __FILE__, __LINE__,); goto error;}

#define check_mem(A) check((A), "Out of memory") 

#endif
