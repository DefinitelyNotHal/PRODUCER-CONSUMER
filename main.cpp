#include "buffer.h"
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>/* required for rand() */
#include <windows.h>
using namespace std;


///figure 5.24 buffer
/* the buffer */
buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t fullSem;
sem_t emptySem;
int numBufferItems;
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void initialization();
void *producer(void *param);
void *consumer(void *param);

///figure 5.25 main function initialize the buffer and create the separate producer and consumer threads
///once it creates threads, it will sleep for a period of time, then awake to terminate the application
///3 parameters: 1. the length of sleeping time. 2. # of producer threads. 3. # of consumer threads.
int main(int argc, char *argv[])
{
/* 1. Get command line arguments argv[1],argv[2],argv[3] */
    if (argc != 4)
    {
        cout<<"Please respectively input the length of sleeping time, # of producer threads, and # of consumer threads.\n"<<endl;
        return 0;
    }
    if ((atoi(argv[1])<0)||(atoi(argv[2])<0)||(atoi(argv[3])<0))
    {
        cout<<"please enter a positive number that is greater than 0.\n"<<endl;
        return 0;
    }
    int lengthSleepT=atoi(argv[1]);//main sleeping time
    int numProducer=atoi(argv[2]);//number of producers
    int numConsumer=atoi(argv[3]);//number of consumers
/* 2. Initialize buffer */
    initialization();
/* 3. Create producer thread(s) */
    for(unsigned int i=0;i<numProducer;i++)
    {
        pthread_t tid; //the thread identifier
        pthread_attr_t attr; //set of thread attributes
        pthread_attr_init(&attr);//obtain default attributes
        pthread_create(&tid,&attr,producer,NULL);//create producer thread
        pthread_join(tid,NULL);//make sure thread exits
    }

/* 4. Create consumer thread(s) */
    for(unsigned int i=0;i<numConsumer;i++)
    {
        pthread_t tid; //the thread identifier
        pthread_attr_t attr; //set of thread attributes
        pthread_attr_init(&attr);//obtain default attributes
        pthread_create(&tid,&attr,consumer,NULL);//create producer thread
        pthread_join(tid,NULL);//make sure thread exits
    }
/* 5. Sleep */
    Sleep(lengthSleepT);
/* 6. Exit */
    return 0;
}
void initialization()
{
    //initialize buffer
    numBufferItems=0;
    /* create the mutex lock */
    pthread_mutex_init(&mutex,NULL);
    //unnamed semaphore
    //3 parameters: 1. a pointer to semaphore. 2. a flag of level of sharing. 3. semaphore's initial value
    /* Create the semaphore and initialize it to BUFFERSIZE */
    sem_init(&emptySem, 0, BUFFER_SIZE);
    /* Create the semaphore and initialize it to 0 */
    sem_init(&fullSem, 0, 0);
}
///figure 5.9 and 5.10 insert_item() and remove_item functions will synchronize the pro and con
///the buffer also needs an initiallization function that initializes the mutual-exclusion
///object mutex along with the empty and full semaphores.
int insert_item(buffer_item item)
{
/* insert item into buffer
return 0 if successful, otherwise
return -1 indicating an error condition */
    if (numBufferItems<BUFFER_SIZE)//check if buffer is full, if full, producer has to wait
    {
        buffer[numBufferItems]=item;
        numBufferItems++;
        return 0;//it is successful
    }
    else
    {
        return -1;//error condition
    }
}

int remove_item(buffer_item *item)
{
/* remove an object from buffer
placing it in item
return 0 if successful, otherwise
return -1 indicating an error condition */
    if (numBufferItems>0)//check if buffer is empty, if empty, then consumer has to wait
    {
        *item=buffer[numBufferItems-1];
        numBufferItems--;
        return 0;//successful
    }
    else
    {
        return -1;//error condition
    }
}

///creating threads using Pthreads API in section 4.4.1.
///section 5.9.4 creating mutex locks and semaphores using Pthreads
///Pthreads Synchronization

///figure 5.26 an outline for producer and consumer threads
///figure 5.9 the structure of the producer process
void *producer(void *param)
{
    buffer_item item;
    while (true)
    {
    /* sleep for a random period of time */
    Sleep(rand()/RAND_MAX);//We don't want it wait too long
    /* generate a random number */
    item = rand();//produce an item in next_produced
    /* acquire the semaphore */
    sem_wait(&emptySem);//wait(empty)
    /* acquire the mutex lock */
    pthread_mutex_lock(&mutex);//wait(mutex)
    /* add next_produced to the buffer */
    /* critical section */
    if (insert_item(item))
    {
        cout<<"report error condition";
    }
    else
    {
        cout<<"producer produced "<<item<<endl;
    }
    /* release the mutex lock */
    pthread_mutex_unlock(&mutex);//signal(mutex)
    /* release the semaphore */
    sem_post(&fullSem);//signal(full)
    }
}
///figure 5.10 the structure of the consumer process
void *consumer(void *param)
{
    buffer_item item;
    while (true)
    {
    /* sleep for a random period of time */
    Sleep(rand()/RAND_MAX);//we don't want it wait too long
    /* acquire the semaphore */
    sem_wait(&fullSem);//wait(full)
    /* acquire the mutex lock */
    pthread_mutex_lock(&mutex);//wait(mutex)
    /* remove an item from buffer to next_consumed */
    if (remove_item(&item))
    {
        cout<<"report error condition";
    }
    else
    {
        cout<<"consumer consumed "<<item<<endl;
    }
    /* release the mutex lock */
    pthread_mutex_unlock(&mutex);//signal(mutex)
    /* release the semaphore */
    sem_post(&emptySem);//signal(empty)
    }
}
