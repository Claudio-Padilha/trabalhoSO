#include <creator.h>

void * startCreator (process * ps, entryQueue * entry, int n, timer * t)                          // ps is a ordered list of all the processes. comes from disk.
{
    
    process * prev;
    sleep(ps->arrivalTime);

    pthread_mutex_lock(&t->lock);
        t->currentTime += ps->arrivalTime;                                  // update current time
    pthread_mutex_unlock(&t->lock);

    pthread_mutex_lock(&entry->lock);
        prev = ps;
        insertIntoQueue(ps, entry);
        ps = ps->next;
    pthread_mutex_unlock(&entry->lock);

    for (int i = 1; i<n; i++)
    {
        sleep(ps->arrivalTime - prev->arrivalTime);                         // wait until next moment it has to create another process
        
        pthread_mutex_lock(&entry->lock);
            prev = ps;
            insertIntoQueue(ps, entry);
            ps = ps->next;
        pthread_mutex_unlock(&entry->lock);

    }
}