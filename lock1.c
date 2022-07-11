#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
pthread_mutex_t mutex;
int i;
void *job1(void *a)
{
   pthread_detach(pthread_self());
   while(1)
   {
	   if(i>=100)break;
   pthread_mutex_lock(&mutex);
    while(i<100)
	{
		if(i%2==0)break;
	   i++;
	   
	}
   printf("i is %d\n",i);
   
   pthread_mutex_unlock(&mutex);
   usleep(1000);
   }
}
void *job2(void *a)
{
   pthread_detach(pthread_self());
   while(1)
   {
	   if(i>=100)break;
   pthread_mutex_lock(&mutex);
    while(i<100)
	{
		if(i%2==1)break;
	   i++;
	   
	}
	printf("i is %d\n",i);
	pthread_mutex_unlock(&mutex);
	usleep(1000);
   }
}
int main()
{
	i=0;
	pthread_t pid1,pid2;
	pthread_mutex_init(&mutex,NULL);
    pthread_create(&pid1,NULL,job1,NULL);
    pthread_create(&pid2,NULL,job2,NULL);

    
    pthread_mutex_destroy(&mutex);
	while(1);
    return 0;
}
