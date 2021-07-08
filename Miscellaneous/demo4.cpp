//masterchef and waiter
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
	sem_init(&empty,0,3);
	sem_init(&full,0,0);
	pthread_mutex_init(&lock1,0);
}

void * masterchef(void * arg)
{
    int* masterchef_id = (int*)arg;
	printf("I am masterchef %d\n",(int*)arg);
	int i;
	while(true)
	{
		sem_wait(&empty);

		pthread_mutex_lock(&lock1);
		sleep(1);
		q1.push(cnt);
		printf("masterchef %d has called waiter to collect order %d\n", masterchef_id, cnt);
		cnt++;
		pthread_mutex_unlock(&lock1);

		sem_post(&full);
	}
}

void * waiter(void * arg)
{

    printf("I am waiter\n");
	int i;
	while(true)
	{
        sem_wait(&full);

		pthread_mutex_lock(&lock1);
		sleep(1);
		int item = q1.front();
		q1.pop();
		printf("\n waiter has delivered order %d\n", item);
		pthread_mutex_unlock(&lock1);

        sem_post(&empty);
	}
}


int main(void)
{
	pthread_t thread1[3];
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;
    int x[3] = {1, 2, 3};

	init_semaphore();

	for (int i = 0; i < 3; i++){
        pthread_create(&thread1[i], NULL, masterchef, (void*) *(x+i));
	}

	pthread_create(&thread2, NULL,waiter, NULL);

	while(1);
	return 0;
}
