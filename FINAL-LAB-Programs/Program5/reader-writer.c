#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5
int b;
int readcount;
sem_t mutex, wrt;

//2 binary semaphores are used to solve this problem

//wrt or write mutex only to signal write
//the other mutex is to increment read count, as it is a shared vairbale
//it belongs to the critical section of all the readers and hence needs a mutex

//mutual exclusion bounded wait progress

void* w(void* p)
{
    int i = 1;
    for(i = 0; i < N; i++){
        sem_wait(&wrt);             //wait
        b = i;
        i++;
        //Writing is performed
        printf("\nW : written = %d",b);
        sem_post(&wrt);             //signal
        printf("\nWriter going to sleep..\n");
        sleep(2);
    }
    printf("\nWriter is living\n");
    return p;
}

void *r(void * a)
{
    int *rr =(int *) a ;
    int i;
    for(i = 0; i < N; i++){
        
        //check if first reader, if so then wait on write to prevent the writer from entering
        sem_wait(&mutex);
        readcount++;
        if(readcount == 1)
        sem_wait(&wrt);
        sem_post(&mutex);
        
        
        //Reading is performed
        printf("\nR : read = %d Reader number = %d \n",b,*rr);
        printf("\nReader %d : going to sleep ",*rr);
        sleep(2);

        
        sem_wait(&mutex);
        readcount--;
        if(readcount == 0)             //to check last reader
        sem_post(&wrt);
        sem_post(&mutex);

        
        //first reader locks it, last will unlockk reader higher priority than writerhere
        
        //if the reader is the last one then signal on write as no more readers
        //the writer can write peacefully


    }
    printf("\nReader number = %d living \n",*rr);
    return a;
}



int main(){
    pthread_t w1, w2, r1, r2;
    int rr1 = 1, rr2 = 2;
    b = 0;
    readcount = 0;
    printf("\n Value of shared variable is %d \n",b);
    
    //pshared is 0 so cannot be shafred to externa; process
    
    sem_init(&(wrt), 0, 1);
    sem_init(&(mutex), 0, 1);

    //Creating Threads
    pthread_create(&w1, NULL, w, (void * )&rr1);
    pthread_create(&r1, NULL, r, (void * )&rr1);
    pthread_create(&r2, NULL, r, (void * )&rr2);
    pthread_join(w1, NULL);
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
   return 0; 
}


/*
Another interesting sync
There are many readers and writers

There can be any number of readers accessing the critical section
Howver at any given time, there can only be 1 writer

For the writer it is very simple as : wait(write_mutex)
                                        write
                                    signal(write_mutex)

For the readers                 wait mutex()
                                    On reader count += 1
                                    wait(write_mutex)
                                signal mutex()

                                wait mutex()
                                    On reader cont == 0
                                        signal (write_mutex)
                                signal(mutex)
                the last reader must signal mutex to ensure tht it is free for witer now
*/