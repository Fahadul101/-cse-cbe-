#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t onion;
sem_t chili;
sem_t egg;
sem_t salt;
sem_t Done;


void *cook()
{
  while(1)
  {
  sem_wait(&Done);
   int r=rand()%3;

   switch (r) {
     case 0: printf("Add 1 Onion:\n");
             sem_post(&onion);
              break;
     case 1:printf("Add 2 Chili Peppers:\n");
             sem_post(&chili);
              break;
     case 2:printf("Add Egg:\n");
            sem_post(&egg);
             break;
     case 3:printf("Add Salt:\n");
            sem_post(&salt);
             break;
   }
   sleep(rand()%5);
 }
}
void *Omelet_1()
{
  while(1){

         sem_wait(&onion);
         sleep(rand()%6);
         printf("1st Omelet Prepared\n");
         sem_post(&Done);

  }

}
void *Omelet_2()
{
  while(1){

        sem_wait(&chili);
        sleep(rand()%6);
        printf("2nd Omelet Prepared\n");
        sem_post(&Done);

  }
}
void *Omelet_3()
{
  while(1){

          sem_wait(&egg);
          sleep(rand()%6);
          printf("3rd Omelet Prepared\n");
          sem_post(&Done);

  }

}
void *Omelet_4()
{
  while(1){

      sem_wait(&salt);
      sleep(rand()%6);
      printf("4th Omelet Prepared\n");
      sem_post(&Done);

  }

}
int main() {

   sem_init(&onion,0,0);
   sem_init(&chili,0,0);
   sem_init(&egg,0,0);
   sem_init(&salt,0,0);
   sem_init(&Done,0,1);
   pthread_t s1,s2,s3,t;
   pthread_create(&s1,NULL,Omelet_1,NULL);
   pthread_create(&s1,NULL,Omelet_2,NULL);
   pthread_create(&s2,NULL,Omelet_3,NULL);
   pthread_create(&s3,NULL,Omelet_4,NULL);
   pthread_create(&t,NULL,cook,NULL);
   pthread_join(s1,NULL);
   pthread_join(s2,NULL);
   pthread_join(s3,NULL);
   pthread_join(t,NULL);
  return 0;
}
