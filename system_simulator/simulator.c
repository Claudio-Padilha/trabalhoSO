/*  Alunos: Cláudio Padilha da Silva, RGA: 201719040036
            Caio Riyousuke Miyada Tokunaga, RGA: 201719040028
            Rodrigo Schio Wengenroth Silva, RGA: 201719040010    
           
    Estrutura de diretórios: A pasta raiz é a trabalhoSO. Dentro dela existe a pasta system_simulator. Dentro desta o arquivo simulator.c é a main.
    É quem controla a execução, chama as threads dos escalonadores e do creator e crias as estruturas (disco, memória, processos, timer e as filas). As 
    threads do shiper, do swapper e do timer são criadas internamente (em outras threads). Ainda dentro do diretório system_simulator, há um diretório
    específico para componente do sistema (cada estrutura e thread) citados anteriormente. Dentro de cada diretório, cada componente tem o seu arquivo.c
    arquivo.h. Os arquivos possuem comentários explicando o funcionamento e características de cada componente.

    Compilação: Dentro do diretório trabalhoSO existe um make file para compilar todos os arquivos e gerar um executável chamado "simulator" dentro do
    próprio diretório. Digit simplesmente make no terminal, dentro do diretório do arquivo make file.

    Execução: Dentro do diretório trabalhoSO após o make, irá aparecer o executável simulator. Digite simplesmente ./simulator no terminal para rodar.

    Entrada: Implementação que recebe números inteiros positivos, separados por espaços como parâmetros de entrada via linha de comando, seguindo as 
    especificações do item 5 - T1:5) do enunciado do trabalho.
*/

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "cpu/cpu.h"
#include "creator/creator.h"
#include "disc/disc.h"
#include "memory/memory.h"
#include "process/process.h"
#include "queue/queue.h"
#include "scheduler/scheduler.h"
#include "shipper/shipper.h"
#include "swapper/swapper.h"
#include "timer/timer.h"

int main ()
{
    int memorySize;
    int numberProcesses;
    int timeQuantum;
    int pid;
    int processSize;
    int creationTime;
    int burst;
    process * p = NULL;

    if (scanf("%d %d %d", &memorySize, &numberProcesses, &timeQuantum))         // Reads main memory size, number of processes and time quantum parameters.
    {}  // if avoids warning

    disc * d = newDisc(numberProcesses);                                                           // Creates new disc
    memory * m = newMemory(memorySize);                                             // Creates new memory
    queue * entry = newQueue();                                                     // Creates new entry queue
    queue * ready = newQueue();                                                       // Creates new ready queue
    timer * t = newTimer(timeQuantum, numberProcesses);                                    // Creates new timer

    struct tm * currentTime;
    time_t segundos;
    time(&segundos);   
    currentTime = localtime(&segundos);
    printf("Time: %d:%d:%d - Inicio da observacao.\n", currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);

    for (int i = 0; i < numberProcesses; i++)                               
    {
        if(scanf("%d %d %d %d", &pid, &processSize, &creationTime, &burst))      // Reads a process parameters. 
        {}  // if avoids warning
        p = newProcess(pid, processSize, creationTime, burst);                      // Creates the processes

        pthread_mutex_lock(&d->lock);                                                   
            d->storage[i] = p;                                                          // Puts created process in disk
        pthread_mutex_unlock(&d->lock);

        pthread_t cr;
        creatorArgs * crArgs = (creatorArgs *) malloc(sizeof(creatorArgs));
        pthread_mutex_lock(&entry->lock);
        crArgs->entry = entry;
        pthread_mutex_unlock(&entry->lock);
        crArgs->p = p;
        pthread_create(&cr, NULL, creator, (void *) crArgs);                        // Creates a creator thread for each process
    }

    pthread_mutex_lock(&entry->lock);
    pthread_mutex_lock(&d->lock);
    pthread_mutex_lock(&m->lock);
    pthread_mutex_lock(&ready->lock);
    pthread_mutex_lock(&t->lock);

    pthread_t fcfs;
    fcfsArgs * fcArgs = (fcfsArgs *) malloc(sizeof(fcfsArgs));
    fcArgs->d = d;
    fcArgs->entry = entry;                                                          // Gets arguments for FCFS scheduler
    fcArgs->m = m;
    fcArgs->ready = ready;
    fcArgs->t = t; 

    pthread_mutex_unlock(&entry->lock);
    pthread_mutex_unlock(&d->lock);
    pthread_mutex_unlock(&m->lock);
    pthread_mutex_unlock(&ready->lock);
    pthread_mutex_unlock(&t->lock);
    
    pthread_create(&fcfs, NULL, schedulerFCFS, (void *) fcArgs);                    // Creates scheduler FCFS

    pthread_mutex_lock(&d->lock);
    pthread_mutex_lock(&m->lock);
    pthread_mutex_lock(&ready->lock);
    pthread_mutex_lock(&t->lock);

    pthread_t rr;
    rrArgs * roundArgs = (rrArgs *) malloc(sizeof(rrArgs));
    roundArgs->d = d;
    roundArgs->m = m;                                                            // Gets arguments for RR scheduler
    roundArgs->ready = ready;           
    roundArgs->t = t;

    pthread_mutex_unlock(&d->lock);
    pthread_mutex_unlock(&m->lock);
    pthread_mutex_unlock(&ready->lock);
    pthread_mutex_unlock(&t->lock);

    pthread_create(&rr, NULL, schedulerRR, (void *) roundArgs);                    // Creates scheduler RR
 
    pthread_mutex_lock(&t->lock);
    pthread_cond_wait(&t->condEnd, &t->lock);                           // Waits for timer signal to end the execution
    pthread_mutex_unlock(&t->lock);

    time(&segundos);   
    currentTime = localtime(&segundos);
    printf("Time: %d:%d:%d - Termino da observacao.\n", currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);

    return 0;
}