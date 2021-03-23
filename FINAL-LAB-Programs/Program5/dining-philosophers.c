#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include<unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N
 
/*
The philosophers's are seayed in a circular tabl nd eed to pick forks to eat
Only if they have both left and right thrn can eat
Hungry eat Think
The shared resource is the fork that ecists between pairs of philosopher's and not the rice or all forks

wait(i)
wait(i+1)
eat
signal(i)
signal(i+1)
think
sem_post() increments (unlocks) the semaphore pointed to by sem.
       If the semaphore's value consequently becomes greater than zero,
       then another process or thread blocked in a sem_wait(3) call will
       be woken up and proceed to lock the semaphore.

sem_wait() does the opposite and reduces the value of the semaohore

*/

//binary semaphores place initialise the value to 1
//to maintain what is what

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };
 

//binary and counting semaphore
sem_t mutex;
sem_t S[N];
 

 //countting semaphore and mutex 
void test(int phnum)
{
    if (state[phnum] == HUNGRY
        && state[LEFT] != EATING
        && state[RIGHT] != EATING) {
        // state that eating
        state[phnum] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n",
                      phnum + 1, LEFT + 1, phnum + 1);
 
        printf("Philosopher %d is Eating\n", phnum + 1);
        // sem_post(&S[phnum]) has no effect
        // during takefork
        // used to wake up hungry philosophers
        // during putfork
        sem_post(&S[phnum]);
    }
}
 
// take up chopsticks
void take_fork(int phnum)
{
    sem_wait(&mutex);
    // state that hungry
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);
    // eat if neighbours are not eating
    test(phnum);
    sem_post(&mutex);
    // if unable to eat wait to be signalled
    sem_wait(&S[phnum]);
    sleep(1);
}
 
// put down chopsticks
void put_fork(int phnum)
{ 
    sem_wait(&mutex);
    // state that thinking
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n",
           phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);
    test(LEFT);
    test(RIGHT); 
    sem_post(&mutex);
}
 

void* philospher(void* num)
{
    while (1) {
        int* i = (int *)num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}
 

//sem_init(semaphore, pshared, value)
//the pshared determines if the semaphore has interprocess scope
//if ZERO, which is mostly assigned to NO interprocess SCOPE, only can be shared between threads


//use a counting semaphore



//all are shared only among the threads, so the value of pshared will be 0 in the semphore initialisation



//u basically have one 
int main()
{
     int i;
    pthread_t thread_id[N];
    // initialize the semaphores
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)
         sem_init(&S[i], 0, 0);
 
    for (i = 0; i < N; i++) {
 
        // create philosopher processes
        //pthread_create(&thread_id[i], NULL, philospher, &phil[i]);
         pthread_create(&thread_id[i], NULL, philospher, (void*)&(i+1));
         printf("Philosopher %d is thinking\n", i + 1);
    } 
    for (i = 0; i < N; i++)
         pthread_join(thread_id[i], NULL);
    return 0;
}
