#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<queue>
#include<stdlib.h>
#include<unistd.h>
using namespace std;

sem_t empty;
sem_t full;
pthread_mutex_t lock1;

queue<int> q1;
int cnt = 0;


void init_semaphore()
{
	sem_init(&empty,0,10);
	sem_init(&full,0,3);
	pthread_mutex_init(&lock1,0);
}

void * customer(void * arg)
{
    int* customer_id = (int*)arg;
	printf("I am customer %d\n",(int*)arg);
	int i;
	while(true)
	{
		sem_wait(&empty);

		pthread_mutex_lock(&lock1);
		sleep(1);
		q1.push(cnt);
		printf("customer %d has placed his order %d\n", customer_id, cnt);
		cnt++;
		pthread_mutex_unlock(&lock1);

		sem_post(&full);
	}
}

void * chef(void * arg)
{
    int* chef_id = (int*)arg;
    printf("I am chef\n");
	int i;
	while(true)
	{
        sem_wait(&full);

		pthread_mutex_lock(&lock1);
		sleep(1);
		int item = q1.front();
		q1.pop();
		printf("chef has prepared order %d\n",chef_id, item);
		item++;
		pthread_mutex_unlock(&lock1);

        sem_post(&empty);
	}
}


int main(void)
{
	pthread_t thread1[10];
	pthread_t thread2[3];
	pthread_t thread3;
	pthread_t thread4;
    int x[10] = {1, 2, 3, 4, 5,6,7,8,9,10};
	int y[3]={1,2,3};

	init_semaphore();

	for (int i = 0; i < 10; i++){
        pthread_create(&thread1[i], NULL, customer, (void*) *(x+i));
	}

	for(int j=0; j< 3 ; j++){
	   pthread_create(&thread2[j], NULL, chef,(void*) *(y+j) );
	}

	while(1);
	return 0;
}
