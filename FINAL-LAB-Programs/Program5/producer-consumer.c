#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#define buffersize 10
pthread_mutex_t mutex;
pthread_t tidP[20],tidC[20];
sem_t full,empty;
int counter;
int buffer[buffersize];
//for the producer consumer problem, make use of 2 counting semaphores and 1 binary semaphore
//one is empty ==> size of the buffer
//second is full ==> 0
//third is a mutex or binary semaphore

//for the producer
/*
	will produce
	wait on empty i.e size of empty reduces
	wait on mutex
	 enter value to buffer
	signal mutex
	signal full, i.e increase the number of contents
*/

/*
for the consumer
consumer{
	wait(full) , u need to decrement the number of contents
	wait(mutex)
		retrieve the content
	signal(mutex)
	signal(empty)

	The reason for enclosing the retriebe and write content in a wait, 
	
	signal block is to prevent reading and writing from happening at the same point of time
	
}

*/

void initialize()
{
	pthread_mutex_init(&mutex,NULL);
	sem_init(&full,1,0);
	sem_init(&empty,1,buffersize);
	counter=0;
}

void write(int item)
{
	buffer[counter++] = item;
}

int read()
{
	return(buffer[--counter]);
}

void * producer (void * param)
{
	int waittime, item, i;
	item = rand() % 5;
	waittime = rand() % 5;
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	printf("\nProducer has produced item: %d\n",item);
	write(item);
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	return param;
}

void * consumer (void * param)
{
	int waittime, item;
	waittime = rand() % 5;
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	item = read();
	printf("\nConsumer has consumed item: %d\n",item);
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	return param;
}

int main()
{
	int n1, n2, i;

	//order cannot be predetermined as such, will execute randonm
	//n produces, m consumers
	initialize();
	printf("\nEnter the no of producers: ");
	scanf("%d",&n1);
	printf("\nEnter the no of consumers: ");
	scanf("%d",&n2);
	for(i = 0; i < n1; i++)
		pthread_create(&tidP[i], NULL, producer, NULL);
	for(i = 0; i < n2; i++)
		pthread_create(&tidC[i], NULL, consumer, NULL);
	for(i = 0; i < n1; i++)
		pthread_join(tidP[i], NULL);
	for(i = 0; i < n2; i++)
		pthread_join(tidC[i], NULL);

	//sleep(5);
	exit(0);
}


/*In the producer consumer process, 
There is a process producing a value and storing it into a buffer
There is anothe process that is consuming from the bufer

2 cases -> feed to buffer by producer (overflow)
		-> demand from empty buffer (underflow)
	This needs tp be regulated

full -> 0
empty -> 5 
mutex() -> binary semaphore (0 ot 1)
if 1 means locked else free

2operations signal and wait
signal += 1
wait -= 1

producer -> always wait on mutex when producing or consuming as it is waiting on a shared resource

producer   wait(mutex)
		   wait(empty)
		   signal(full)
		   signal(mutex)

consumer  wait(mutex)
		  signal(empty)
		  wait(full)
		  signal(mutex)	


*/