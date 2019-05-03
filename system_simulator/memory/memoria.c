#include <processo.h> 

typedef struct memory
{
    process * buffer;       // memory is represented by a list. This points to the first process of the list
    int used;               // amount of memory used          
    int size;               // total storage capacity
} memory;

