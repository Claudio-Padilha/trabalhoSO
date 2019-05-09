// main. 


/* EXAMPLE CODE

                                                                  
#define _OPEN_THREADS                                                           
#include <stdio.h>                                                              
#include <pthread.h>                                                            
                                                                                
void *thread1(void *arg)                                                        
{                                                                               
   printf("hello from the thread\n");                                           
   pthread_exit(NULL);                                                          
}                                                                               
                                                                                
int main()                                                                      
{                                                                               
   int            rc, stat;                                                     
   pthread_attr_t attr;                                                         
   pthread_t      thid;                                                         
                                                                                
   rc = pthread_attr_init(&attr);                                               
   if (rc == -1) {                                                              
      perror("error in pthread_attr_init");                                     
      exit(1);                                                                  
   }                                                                            
                                                                                
   rc = pthread_create(&thid, &attr, thread1, NULL);                            
   if (rc == -1) {                                                              
      perror("error in pthread_create");                                        
      exit(2);                                                                  
   }                                                                            
                                                                                
   rc = pthread_join(thid, (void *)&stat);                                      
   exit(0);                                                                     
}                                                                               


*/