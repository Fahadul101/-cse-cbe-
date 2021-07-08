#include<stdio.h>
#include<pthread.h>

void * cThread(void * u){
    printf("Carboon Tread\n");
}
void * oThread(void * u){
    printf("Oxyzen Thread\n");
}
int main()
{
    pthread_t carboon,oxyzen,oxyzen2;
    pthread_create(&carboon,NULL,&cThread,NULL);
    pthread_create(&oxyzen,NULL,&oThread,NULL);
    pthread_create(&oxyzen2,NULL,&oThread,NULL);

    pthread_join(carboon,NULL);
    pthread_join(oxyzen,NULL);
    pthread_join(oxyzen2,NULL);

    printf("CO2 is produced");
    return 0;
}
