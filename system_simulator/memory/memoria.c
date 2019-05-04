#include <memoria.h>


memory * newMemory ()
{
    memory * m = (memory *) malloc(sizeof(memory));
    m->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return m;
}

void * processIntoMemory (process * p, memory * mem)
{
    pthread_mutex_lock(&mem->lock);                                     // aquire memory lock           
        process * aux = mem->list;                                      // gets first process on the list
        if (aux == NULL || aux->id > p->id)                             // it goes on the first position
        {
            p->next = mem->list;
            mem->list = p;
        }else
        {
            while (aux->next != NULL && aux->next->id < p->id)           // searches for the process position on the list
            {
                aux = aux->next;
            }

            p->next = aux->next;
            aux->next = p;
        }
    pthread_mutex_unlock(&mem->lock);                                     // releases memory lock
}