

#include<bits/stdc++.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<queue>
#include<stdlib.h>
#include<unistd.h>
using namespace std;

sem_t shalon; 
sem_t e_sofa; 
sem_t b_chair; 
sem_t b_ready; 
sem_t finished; 
sem_t payment; 
sem_t receipt; 

queue<int> shop; 
queue<int> sofa; 
queue<int> chair;
queue<int> barbar;
queue<int> paymnt;


pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_mutex_t lock3;
pthread_mutex_t lock4;
pthread_mutex_t lock5;
pthread_mutex_t lock6;
void init_semaphore()
{

	sem_init(&shalon,0,10);
	sem_init(&e_sofa,0,4);
	sem_init(&b_chair,0,3);
	sem_init(&b_ready,0,3);
	sem_init(&b_ready,0,0);
	sem_init(&finished,0,0);
	sem_init(&payment,0,0);
	sem_init(&receipt,0,0);
}
int cnt = 0;
int cut = 0;
int seat_sofa;
int getup_sofa;
int seat_chair;
int take_payment;
void * customer(void * arg)
{

    int* customer_id = (int*)arg;
        printf("Customer %d\n",customer_id);
    sem_wait(&shalon);
        printf("customer number %d\n",customer_id);
    cnt++;
    shop.push(cnt);

			sem_wait(&e_sofa); 
				sleep(1);
			pthread_mutex_lock(&lock1);
				int push_sofa=shop.front();
			sofa.push(push_sofa);

    shop.pop();
       printf("seat sofa %d\n",push_sofa);
    pthread_mutex_unlock(&lock1);
    sleep(1);
			sem_wait(&b_chair); 
			pthread_mutex_lock(&lock2);
			int push_chair=sofa.front();
    printf("Leave sofa %d\n",push_chair);
			chair.push(push_chair);
    sofa.pop();
			pthread_mutex_unlock(&lock2);
    sleep(1);

    pthread_mutex_lock(&lock3);
		int push_customer=chair.front();
    barbar.push(push_customer);
    chair.pop();
		printf("Seat barber chair %d\n",push_customer);
			sem_post(&b_ready);
			sem_post(&e_sofa);
    pthread_mutex_unlock(&lock3);


    sem_wait(&finished);
		pthread_mutex_lock(&lock5);
    take_payment=paymnt.front();
    paymnt.pop();
		printf("payment %d\n",take_payment);
    sem_post(&payment);
    sem_wait(&receipt);
		printf("Exit shop %d\n",take_payment);
    pthread_mutex_unlock(&lock5);
    sem_post(&shalon);
}



void * barber(void * arg)
{
    int* barber_id = (int*)arg;
	while(true){

            sem_wait(&b_ready);
            sleep(2);
				pthread_mutex_lock(&lock4);
            int hair_cut_customer=barbar.front();
				paymnt.push(hair_cut_customer);
            barbar.pop();
				printf("Barber %d cutting hair %d\n",barber_id, hair_cut_customer);
            sem_post(&finished);
				pthread_mutex_unlock(&lock4);
            sem_post(&b_chair);

	}
}
void * cash_rechive(void * arg)
{
	while(true)
	{
		sem_wait(&payment);
        printf("Accept payment from %d\n",take_payment);
        sem_post(&receipt);
	}

}

int main(void)
{
   
	pthread_t thread1[10];
	pthread_t thread2[3];
	pthread_t thread3;
    int x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int y[3] = {1, 2, 3};
    init_semaphore();



	for (int i = 0; i < 10; i++){
        pthread_create(&thread1[i], NULL, customer, (void*) *(x+i));
	}
    for(int i = 0; i < 3; i++){
	   pthread_create(&thread2[i], NULL, barber, (void*) *(y+i));
    }
    pthread_create(&thread3,NULL,cash_rechive,NULL);




	while(1);
	return 0;
}
