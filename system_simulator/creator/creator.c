#include <creator.h>

void * startCreator (process * ps, entryQueue * entry, int n)                          // ps is a ordered list of all the processes. comes from disk.
{
    
    process * prev;
    sleep(ps->arrivalTime);
    pthread_mutex_lock(&entry->lock);
        prev = ps;
        insertIntoQueue(ps, entry);
        ps = ps->next;
    pthread_mutex_unlock(&entry->lock);

    for (int i = 1; i<n; i++)
    {
        sleep(ps->arrivalTime - prev->arrivalTime);
        pthread_mutex_lock(&entry->lock);
            prev = ps;
            insertIntoQueue(ps, entry);
            ps = ps->next;
        pthread_mutex_unlock(&entry->lock);

    }
}