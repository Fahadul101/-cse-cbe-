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

void * chef(void * arg)
{
    int* chef_id = (int*)arg;
	printf("I am chef %d\n",(int*)arg);
	int i;
	while(true)
	{
		sem_wait(&empty);

		pthread_mutex_lock(&lock1);
		sleep(1);
		q1.push(cnt);
		printf("chef %d has sent order %d to masterchef", chef_id, cnt);
		cnt++;
		pthread_mutex_unlock(&lock1);

		sem_post(&full);
	}
}

void * masterchef(void * arg)
{

    printf("I am masterchef\n");
	int i;
	while(true)
	{
        sem_wait(&full);

		pthread_mutex_lock(&lock1);
		sleep(1);
		int item = q1.front();
		q1.pop();
		printf("\n masterchef has checked order %d\n", item);
		pthread_mutex_unlock(&lock1);

        sem_post(&empty);
	}
}


int main(void)
{
	pthread_t thread1[2];
	pthread_t thread2;
    int x[2] = {1, 2};

	init_semaphore();

	for (int i = 0; i < 2; i++){
        pthread_create(&thread1[i], NULL, chef, (void*) *(x+i));
	}

	pthread_create(&thread2, NULL, masterchef, NULL);

	while(1);
	return 0;
}
